#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "Proto_NZ.h"


const int Port = 8888;
int sock_fd =-1,new_fd=-1;
int SeriNUm = 0;

void ha_Exit(int signo) {
	close(sock_fd);
	close(new_fd);
	printf("[sucess]exit>>>>>\n");
	_exit(1);
}

void sendData(int tag, int serialNum)
{
	char* sendBuf;
	const char* deviceID = "wuhuaixi";
	SendDataBack faceRecord = SendDataBack_init_zero;
	strcpy(faceRecord.Id.dev, deviceID);
	faceRecord.SeriNum = ++SeriNUm;
	uint8_t send_pb[1024];
	pb_ostream_t stream = pb_ostream_from_buffer(send_pb, sizeof(send_pb));
	pb_encode_tag(&stream, PB_WT_VARINT, MsgType_SendDataBack_tag);
	bool status = pb_encode(&stream, SendDataBack_fields, &faceRecord);
	if (!status)
	{
		printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
		return ;
	}
	int sendbuf_length = (int)stream.bytes_written;
	printf("发送返回  sendbuf_length: %d\n", sendbuf_length);
	if (new_fd!= -1)
	{
		send(new_fd, send_pb, sendbuf_length, 0);
	}
	else
	{
		printf("new_fd=null...\n");
	}
}

void receiveData(uint8_t* receive_pb,int dataLength)
{
	//uint8_t* receive_pb = (uint8_t*)unDecodeData;
	pb_istream_t istream = pb_istream_from_buffer(receive_pb, (size_t)dataLength);
	
	bool eof = false;
	uint32_t tag = 2;
	pb_wire_type_t write_type = PB_WT_VARINT;
	pb_decode_tag(&istream, &write_type, &tag, &eof);

	SendDataBack photoId = SendDataBack_init_zero;
	bool decode_status;
	int messageType = (int)tag;
	switch (messageType)
	{
		case MsgType_AddFcae_tag:
			printf("server receive tag=MsgType_AddFcae_tag\n");
			sendData(messageType, 272);
		break;
		case MsgType_FaceRecord_tag:
			printf("server receive tag=MsgType_FaceRecord_tag\n");
			sendData(messageType, 272);
		break;
		case MsgType_SendDataBack_tag:
		decode_status = pb_decode(&istream, SendDataBack_fields, &photoId);
		if (!decode_status)
		{
			printf("pb_decode failed: %s\n", PB_GET_ERROR(&istream));
			break;
		}
		printf("server deiceID=%s  SeriNum=%d\n", photoId.Id.dev, photoId.SeriNum);
		break;
		default:
		printf("server receive tag= ERROR\n");
		break;
	}
	//return;
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
		printf("client receive Return rc=%d\n", rc);
		if (rc <= 0)//如果recv返回小于等于0，代表socket已经关闭或者出错了
		{
			printf("Connected Break rc=%d\n", rc);
			break;
		}
		receiveData(undecode_buf, rc);

	}
	return NULL;
}
int main(void) {
	signal(SIGINT, ha_Exit);
	struct sockaddr_in mysock;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);//初始化socket

	memset(&mysock, 0, sizeof(mysock));

	//编辑地址信息
	mysock.sin_family = AF_INET;
	mysock.sin_port = htons(Port);
	mysock.sin_addr.s_addr = INADDR_ANY;

	bind(sock_fd, (struct sockaddr*) & mysock, sizeof(struct sockaddr));//绑定地址，然后监听
	if (listen(sock_fd, 10) < -1) {
		printf("listen error.\n");
	}

	socklen_t sin_size =(socklen_t)sizeof(struct sockaddr_in);
	struct sockaddr_in client_addr;
	
	char buf[1024];
	char sedbuf[1024] = "recv successfully.\n";
	uint8_t buffer[1024];
	int bufferLength =1024;
	int choose = -1;
	//HA_ADD_FACE(buffer, &bufferLength);
	//printf("HA_DELETE_FACEID finish ===%d\n", (int)sizeof(buffer));
	//printf("HA_DELETE_FACEID finish ===%d\n", bufferLength);
	//sendData(1, 2);
	printf("listening...\n");
	new_fd = accept(sock_fd, (struct sockaddr*) & client_addr, &sin_size);//accpet
	pthread_t receiveThread;
	pthread_create(&receiveThread, NULL, recvsocket, &new_fd);
	//pthread_create(&receiveThread, NULL, sendsocket, &new_fd);
	//pthread_join(receiveThread, NULL);
	while (1) {
		printf("请输入操作编码:");
		while (scanf("%d", &choose) != -1)
		{
			memset(&buffer, 0, sizeof(buffer));
			bufferLength = 1024;
			switch (choose)
			{
			case 0:
				//HA_RegFaceRecoCb(cam, getting_face, NULL);
				//HA_GET_SDK_VERSION
				HA_ADD_FACE(buffer, &bufferLength);
				send(new_fd, buffer, bufferLength, 0);
				printf("HA_DELETE_FACEID finish ===%d\n",(int)sizeof(buffer));
				break;
			case 1:
				QUERY_DELETE_FACE(buffer, &bufferLength, 0);
				send(new_fd, buffer, bufferLength, 0);
				printf("QUERY_DELETE_FACE finish  0\n");
				break;
			case 2:
				QUERY_DELETE_FACE(buffer, &bufferLength, 1);
				send(new_fd, buffer, bufferLength, 0);
				printf("QUERY_DELETE_FACE finish  1\n");
				break;
			default:
				break;
			}
			printf("请输入操作编码:");
		}
	}
	close(new_fd);
	close(sock_fd);
	return 0;
}