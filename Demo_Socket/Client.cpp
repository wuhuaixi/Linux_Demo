#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include<iostream>
#include<fstream>
#include <fcntl.h>

#include "Proto_NZ.h"

const int Port = 8888;
int sock_fd = -1;


void sendData(uint8_t* arg, int length)
{
	//char str[10] = { 0 };
	//int getNum=atoi(arg);
	if (sock_fd != -1)
	{
		send(sock_fd, arg, length, 0);
		//printf("sendData %s\n", arg);
	}
	else
	{
		printf("sendData sock_fd 未连接\n");
	}
}
int testProtobuf(char* sendBuf, const char* getString)
{
	FaceRecord faceRecord = FaceRecord_init_zero;

	strcpy(faceRecord.dev.dev, getString);
	strcpy(faceRecord.face.faceID, getString);
	strcpy(faceRecord.face.faceName, getString);
	strcpy(faceRecord.face.userParam, getString);
	strcpy(faceRecord.picture.jpgName, getString);
	strcpy(faceRecord.picture.libName, getString);

	

	uint8_t send_pb[1024];
	pb_ostream_t stream = pb_ostream_from_buffer(send_pb, sizeof(send_pb));
	pb_encode_tag(&stream, PB_WT_VARINT, MsgType_FaceRecord_tag);
	bool status = pb_encode(&stream, FaceRecord_fields, &faceRecord);
	if (!status)
	{
		printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
		return 0;
	}
	int sendbuf_length = (int)stream.bytes_written;
	sendData(send_pb, sendbuf_length);
	return sendbuf_length;
}
void receiveData(const uint8_t* receive_pb,int pb_length)
{
	pb_istream_t istream = pb_istream_from_buffer(receive_pb, (size_t)pb_length);
	bool eof = false;
	uint32_t tag = 99;
	pb_wire_type_t write_type = PB_WT_VARINT;
	pb_decode_tag(&istream, &write_type, &tag, &eof);
	int messageType = (int)tag;
	bool decode_status;
	SendDataBack photoId = SendDataBack_init_zero;
	switch (messageType)
	{
		//case MsgType_SendDataBack_tag:
		//	printf("server receive tag=NZ_MESSAGE_SocketTag_GetVersion_tag \n");
		//	break;
		case MsgType_AddFcae_tag:
			printf("server receive tag=MsgType_AddFcae_tag\n");
			HA_ADD_FACE_REQ(&istream);
			break;
		case MsgType_FaceRecord_tag:
			printf("server receive tag=MsgType_FaceRecord_tag\n");
			break;
		case MsgType_SendDataBack_tag:
			decode_status = pb_decode(&istream, SendDataBack_fields, &photoId);
			if (!decode_status)
			{
				printf("pb_decode failed: %s\n", PB_GET_ERROR(&istream));
				break;
			}
			printf("sendMessaage Success deiceID=%s  SeriNum=%d\n", photoId.Id.dev,photoId.SeriNum);
			break;
		case MsgType_OperationFaceId_tag:
			printf("server receive tag=MsgType_OperationFaceId_tag\n");
			QUERY_DELETE_FACE_REQ(&istream);
			break;
		default:
			printf("server receive tag= ERROR\n");
			break;
	}
}
void* recvsocket(void* arg)//接收server端socket数据的线程
{
	int st = *(int*)arg;
	char s[1024];
	uint8_t undecode_buf[1024];
	while (1)
	{
		memset(s, 0, sizeof(s));
		memset(undecode_buf, 0, sizeof(undecode_buf));
		int rc = recv(st, undecode_buf, sizeof(undecode_buf), 0);
		printf("client receive Return rc=%d\n",rc);
		if (rc <= 0)//如果recv返回小于等于0，代表socket已经关闭或者出错了
		{
			printf("Server Break rc=%d\n", rc);
			break;
		}
		receiveData(undecode_buf, rc);

	}
	return NULL;
}

void* sendsocket(void* arg)//向server端socket发送数据的线程
{
	int st = *(int*)arg;

	char sendbuf[1024];
	while (1)
	{
		memset(sendbuf, 0, sizeof(sendbuf));
		fgets(sendbuf, sizeof(sendbuf), stdin);

		//send(sock_fd, sendbuf, strlen(sendbuf), 0);
		//send(st, sendbuf, strlen(sendbuf), 0);
		//sendData(st, sendbuf);
		char* sendBuf;
		int sendLength = testProtobuf(sendBuf, "test123");//测试protofuf的操作
		if (strcmp(sendbuf, "exit\n") == 0)
			break;
	}
	return NULL;
}
void socket_start()
{
	
	struct sockaddr_in server_addr;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);//初始化socket
	if (sock_fd == -1) {
		printf("%s\n", strerror(errno));
		return;
	}
	bzero(&server_addr, sizeof(server_addr));//编辑服务端地址信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(Port);
	//server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (!inet_aton("192.168.2.219", &server_addr.sin_addr))
	{
		printf("bad address");
	}
	int tmp = connect(sock_fd, (struct sockaddr*)(&server_addr),
		sizeof(struct sockaddr));//连接服务端socket
	if (tmp == -1) {
		printf("connect error%s\n", strerror(errno));
		return;
	}
}

int File_size(const char* filePath)//获取文件名为filename的文件大小。
{
	FILE* fp = fopen(filePath, "rb");//打开文件。
	int size=0;
	if (fp == NULL) // 打开文件失败
		return 0;
	fseek(fp, 0, SEEK_END);//定位文件指针到文件尾。
	size = ftell(fp);//获取文件指针偏移量，即文件大小。
	fclose(fp);//关闭文件。
	return size;
}
int FileRead(const char* imgPath_p, char* imgData_p, int* length_p)
{
	char* imgData;
	char* imgPath = (char*)imgPath_p;
	FILE* imgFile = fopen(imgPath, "rb");
	if (imgFile == NULL)
	{
		printf("read File FAIL path=%s \n", imgPath);
		return 0;
	}
	fseek(imgFile, 0, SEEK_END);//定位文件指针到文件尾。
	int length= ftell(imgFile);
	size_t size_length = sizeof(char);
	rewind(imgFile);  // 函数rewind()把文件指针移到由stream(流)指定的开始处, 同时清除和流相关的错误和EOF标记
	// allocate memory to contain the whole file: 为整个文件分配内存缓冲区
	imgData = (char*)malloc(sizeof(char) * length); // 分配缓冲区，按前面的 lSize
	//imgData = (char*)malloc(length);
	if (imgData == NULL) {
		printf("Memory error\n");
		fclose(imgFile);
		return 0; 
	}  // 内存分配错误，退出2
	// copy the file into the buffer:  该文件复制到缓冲区
	printf("length=%d     imgData=%d \n", length, (int)sizeof(imgData));
	printf("imgPath=%s      \n", imgPath);
	*length_p = length;
	char bufff[1024];
	size_t result = fread(imgData_p, size_length,length, imgFile); // 返回值是读取的内容数量
	if (result != length) { 
		printf("Reading error   result=%d \n",(int)result); 
		fclose(imgFile);
		free(imgData);
		return 0;
	} // 返回值如果不和文件大小，读错误
	fclose(imgFile);
	free(imgData);
	return 1;
}
void openFile()
{
	const char* path = "/home/wuhuaixi/Hi3516/Demo_Socket/NZ170071.jpg";//测试使用图片路径
	const char* path2 = "/home/wuhuaixi/Hi3516/Demo_Socket/234.jpg";//测试使用图片路径
	int size_ev_write = 1024;
	int file_size,file_tg_size;
	printf("File fopen begin \n");
	file_size = File_size(path);
	file_tg_size = File_size(path2);
	if (file_tg_size > 0)
	{
		printf("The Target File was Exist path=%s \n", path);
		printf("The Target File Size=%d \n",file_tg_size);
		return;
	}
	//printf("read path size=%d \n", (int)file_size);
	FILE* out = fopen(path, "rb");
	if (out == NULL)
	{
		printf("read File FAIL path=%s \n", path);
		return;
	}

	FILE* new_file = fopen(path2, "ab+");
	if (new_file == NULL)
	{
		printf("Write new_file FAil path= %s\n", path2);
		return;
	}
	//sleep(1);
	printf("ready to open!\n");
	char bufddd[size_ev_write] = "";
	memset(bufddd, 0, sizeof(bufddd));
	int num_add = 0;
	int num_after = 0;
	size_t size_length = sizeof(char);
	while (num_add < file_size)
	{
		memset(bufddd, 0, sizeof(bufddd));
		num_after = fread(bufddd, size_length, size_ev_write, out);
		//printf("OVER to open num_after=%d\n",num_after);
		fwrite(bufddd, size_length, num_after, new_file);
		num_add = num_add + size_ev_write;
	}
	fclose(out);
	fclose(new_file);
	printf("OVER to write File! file size=%d\n", num_add);
}

int main(void) {
	//openFile ;//文件读写操作
	//const char* path = "/home/wuhuaixi/Hi3516/Demo_Socket/NZ170071.jpg";//测试使用图片路径
	 //char* imgData;//测试使用图片路径
	//int length;
	//FileRead(path, imgData, &length);
	
	pthread_t sendThread, receiveThread;
	socket_start();
	pthread_create(&sendThread, NULL, recvsocket, &sock_fd);
	pthread_create(&receiveThread, NULL, sendsocket, &sock_fd);
	pthread_join(receiveThread, NULL);
	close(sock_fd);
	return 0;
}