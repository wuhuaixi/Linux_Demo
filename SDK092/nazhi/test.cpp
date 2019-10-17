#include <stdio.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "HASdk.h"
#include "Proto_NZ.h"

using namespace std;

HA_Cam* cam=NULL;
int Connected = 0;
const int Port = 8888;
int sock_fd = -1;
bool isConnect = false;

void ha_Exit(int signo){
	printf("[info]exit>>>>>\n");
	HA_DeInit();
	close(sock_fd);
	printf("[sucess]exit>>>>>\n");
	_exit(1);	
}

void sendData(uint8_t* arg, int length)
{
	if (sock_fd != -1)
	{
		send(sock_fd, arg, length, 0);
	}
	else
	{
		printf("sendData sock_fd 未连接\n");
	}
}



void HASDK_CALL DecodeImageCb(struct HA_Cam* cam, unsigned char* rgb, int width, int height, int usrParam){
	printf("w=%d,h=%d\n",width,height);
	
}
void HASDK_CALL ServerConnectEventCb(struct HA_Cam* m_cam, const char* ip, unsigned short port, int event, int usrParam){

	printf("IP=%s,port=%d,event =%d\n", ip, port, event);
	if (port == 8111) {
		printf("抓拍数据上传端口\n");
		return;
	}
	else if(port=7111){
		printf("相机连接\n");
		Connected=1;
		cam=m_cam;
		return;
	}

}

/*
unsigned int sequence;  //抓拍序号，从1开始，每产生一组抓拍数据增加1。
	char camId[32];         //相机编号
	char posId[32];         //点位编号
	char posName[96];       //点位名称

	unsigned int tvSec;     //抓拍时间秒数，从1970年01月01日00时00分00秒至抓拍时间经过的秒数。
	unsigned int tvUsec;    //抓拍时间微秒数，tvSec的尾数

	short isRealtimeData;   //实时抓拍标志，0：非实时抓拍数据。非0：实时抓拍数据。

	short matched;          //比对结果，0：未比对。-1：比对失败。大于0的取值：比对成功时的确信度分数（100分制）。
	char matchPersonId[20]; //人员ID
	char matchPersonName[16];//人员姓名
	int matchRole;          //人员角色，0：普通人员。 1：白名单人员。 2：黑名单人员

	int existImg;           //全景图，是否包含全景图像。0：不包含全景图像。非0：包含全景图像。
	char imgFormat[4];      //全景图像格式
	int imgLen;             //全景图像大小
	unsigned short faceXInImg;//人脸位于全景图像的X坐标。
	unsigned short faceYInImg;//人脸位于全景图像的y坐标
	unsigned short faceWInImg;//人脸位于全景图像宽度
	unsigned short faceHInImg;//人脸位于全景图像高度

	int existFaceImg;       //人脸图，特写图像标志，是否包含特写图像。0：不包含特写图像。非0：包含特写图像。
	char faceImgFormat[4];  //人脸图像封装格式。
	int faceImgLen;         //特写图像大小
	unsigned short faceXInFaceImg;//人脸位于特写图像的X坐标。
	unsigned short faceYInFaceImg;//人脸位于特写图像的y坐标。
	unsigned short faceWInFaceImg;//人脸位于特写图像的宽度
	unsigned short faceHInFaceImg;//人脸位于特写图像的高度

	int existVideo;         //是否包含视频。0：不包含视频。非0：包含视频。
	unsigned int videoStartSec;//视频起始时间（秒）
	unsigned int videoStartUsec;//videoStartSec尾数，微妙
	unsigned int videoEndSec;   //视频结束时间（秒）
	unsigned int videoEndUsec;  //videoEndSec尾数，微妙
	char videoFormat[4];        //视频封装格式。
	int videoLen;               //视频大小

	unsigned char sex;          //性别 0: 无此信息 1：男 2：女
	unsigned char age;          //年龄 0: 无此信息 其它值：年龄
	unsigned char expression;   //表情 0: 无此信息 其它值：暂未定义
	unsigned char skinColour;   //肤色 0: 无此信息 其它值：暂未定义
	unsigned char qValue;       //注册标准分数，分数越高越适合用来注册
	unsigned char sourceOfReg;   //注册来源 0：无此信息 1：注册软件注册  2：无感录入 3：云同步注册
	char attributeOfReg;  //注册人员属性 0:无此信息 1：永久有效名单 2：临时有效名单 3：永久无效名单
	unsigned char living;    //是否活体 0：无此信息 1：活体 2：非活体
	char hatColour; //安全帽颜色  enum HatDetectResult
	char FaceAngle; //人脸扭转角度 (与平面夹角)  -90~90;
	char FaceAngleFlat; // 人脸旋转角度 (在平面上的旋转角度） -90~90;
	char res0;
	unsigned int math_type;		//比对类型  参见 MatchType
	unsigned int wgCardNO;		//  32位韦根卡号
	unsigned long long  wgCardNOLong; //  46位韦根卡号
	char resv[100];				//保留
	unsigned char* img;         //全景图像数据
	unsigned char* faceImg;     //特写图像数据
	unsigned char* video;       //视频数据
	int feature_size;           //当前抓拍人脸的特征数据大小
	float *feature;             //当前抓拍人脸的特征数据
	int modelFaceImgLen;        //模板人脸图像长度
	char modelFaceImgFmt[4];       //模板人脸图像类型
	unsigned char *modelFaceImg;    //模板人脸图像数据
	HA_Point PointInImg[5];  //全景图人脸特征点 需打开全景图
	HA_Point PointInFaceImg[5];  //特写图人脸特征点 需打开特写图
	char dev_id[32];  //设备序列号
	int existIDCard;  //是否存在身份证信息
	char IDCardnumber[36];   // 身份证号码。
	char IDCardname[43];        // 姓名。
	unsigned char IDCardsex;  // 性别。@ref Sex 。
	char IDCardnational[19];   // 民族。
	char IDCardbirth[17];    // 出生日期。
	char IDCardresidence_address[103];   // 住址。
	char IDCardorgan_issue[43];   // 签发机关。
	char IDCardvalid_date_start[17];   // 有效期起始日期。
	char IDCardvalid_date_end[17];   // 有效期截止日期。
	char userParam[68];
*/

 void HASDK_CALL getting_face(struct HA_Cam* cam, const struct FaceRecoInfo* faceRecoInfo, void* usrParam){

	 

	printf("获取到人脸 name=%s id=%s role=%d\n",faceRecoInfo->matchPersonName,faceRecoInfo->matchPersonId,faceRecoInfo->matchRole);
	printf(" tvSec=%d tvUsec=%d isRealtimeData=%d\n", faceRecoInfo->tvSec, faceRecoInfo->tvUsec, faceRecoInfo->isRealtimeData);
	printf(" matched=%d matchRole=%d dev_id=%s\n", faceRecoInfo->matched, faceRecoInfo->matchRole, faceRecoInfo->dev_id);
	printf(" hatColour=%d userParam=%s userParam=%s\n", faceRecoInfo->hatColour, (char*)usrParam, faceRecoInfo->userParam);
	size_t char_length = sizeof(char);
	/*
	if(faceRecoInfo->existFaceImg !=0){
		FILE* fp = fopen("./face.jpg","wb");
		if(!fp){
			printf("fopen error \n");
			return;
		}
		int ret = fwrite(faceRecoInfo->faceImg, 1,faceRecoInfo->faceImgLen,fp);
		//int ret = fwrite(faceRecoInfo->img, 1, faceRecoInfo->imgLen, fp);
		printf(" existFaceImg ret = %d \n",ret);
		fclose(fp);
	} else {
		printf("faceRecoInfo->existImg =0 \n");
	}
	*/
}


long make_time(int year, int month, int mday, int hour, int minute, int second)
{
    struct tm t;

    memset(&t, 0, sizeof(t));

    t.tm_year = year - 1900;
    t.tm_mon  = month - 1;
    t.tm_mday = mday;
    t.tm_hour = hour;
    t.tm_min  = minute;
    t.tm_sec  = second;

    return mktime(&t);
}
int HA_GET_TIME(SystemTime* sysTime)
{
	sysTime->time_zone = 8;
	//sprintf(sysTime.date,"%s","2019/10/5");
	//sprintf(sysTime.time, "%s", "16:10:5");

	//int ret = HA_SetSystemTime(cam,&sysTime);
	size_t ret = HA_GetSystemTime(cam, sysTime);
	printf("ret = %d time = %s : %s >>>>>>>>\n", ret, sysTime->date, sysTime->time);

	//sprintf(sysTime.date,"%s","2019/8/3");
	//sprintf(sysTime.time, "%s", "08:34:23");
	//ret = HA_SetSystemTime(cam,&sysTime);
	//printf("ret = %d time = %s : %s >>>>>>>>\n",ret,sysTime.date,sysTime.time);
	return 0;
}

//HASDK_API int HASDK_CALL HA_DeleteFaceDataByPersonID(HA_Cam* cam,const char* personID);
int HA_LCD_DISPLAY()
{
	char display[100],matchDisplay[100];

	HA_GetLcdDisplayItems(cam, display);
	printf("HA_GetLcdDisplayItems =%s \n", display);

	HA_GetPersonDisplayOptions(cam, matchDisplay);
	printf("HA_GetLcdDisplayItems =%s \n", matchDisplay);
}
int HA_DELETE_FACEID(char* faceID)
{
	int ret=HA_DeleteFaceDataByPersonID(cam, faceID);
	ErrorCheck(ret);
	return ret;
}
int HA_QUERY_FACEID(pb_istream_t* istream)
{
	char flags = 0;
	short mode = 0;//精确查询
	QueryCondition conditon; //查询条件
	char faceID[20];
	int operation,result=-1;
	result=QUERY_DELETE_FACE_REQ(istream, faceID,&operation);
	printf("QUERY_DELETE_FACE_REQ=%d\n", result);
	if (result >= 0)
	{
		if(operation==0)
		{
			HA_DELETE_FACEID(faceID);
			printf("删除成功 faceId=%s\n", faceID);
		}
		else if (operation == 1)
		{
			strcpy(conditon.faceID, faceID);
			//strcpy(conditon.faceName, "XXXXX"); //填需要查询的条件其他可不填
			flags |= QUERY_BY_ID;
			//flags |= QUERY_BY_NAME;//查询条件为 ID+姓名
			int ret = HA_QueryFaceEx(cam, -1, 1, 100, 1, 1, flags, mode,
				&conditon); //按条姓名和 ID 模糊查询 页码为对满足条件的人员进行分页
			if (ret == ERR_NONE)
			{ 
				printf("查询id 存在\n");
				return 1;
			}
			else
				printf("HA_QUERY_FACEID fal=%d\n", ret);
			return -1;
		}
	}
	return 0;
}

/*
struct FaceFlags
{
	char faceID[20];    //人员ID
	char faceName[16];  //人员姓名
	int role;           //人员角色，0：普通人员。 1：白名单人员。 2：黑名单人员。 -1：所有人员。
	unsigned int wgCardNO;//韦根协议门禁卡号
	unsigned int effectTime;   //有效期截止时间，该人员信息在该时间内有效,从1970年1月1日0时0分0秒到截止时间的秒数（0xFFFFFFFF表示永久有效，0表示永久失效） 最大2038 年
	unsigned int effectStartTime;//有效期起始时间，该人员信息在该时间之后有效,从1970年1月1日0时0分0秒到起始时间的秒数（0表示未初始化） 最大2038 年
	short version;           //特征数据版本 用于同步注册特征数据时相机校验 未使用特征数据注册填0;
	unsigned long long  wgCardNOLong;   // 韦根门禁卡号加长 在wgCardNO长度不满足时可将wgCardNO置0使用此成员
	unsigned char ScheduleMode; ////调度模式 0:不使用调度模式  1~5 对应 Struct KindSchedule->ScheduleNameCode模式
	char resv2;
	char userParam[68];  //用户自定义文本内容，可用于相机TTS播放、LCD显示，也可作为用户平台自定义属性使用
	char resv[8104];
};
*/
int HA_ADD_FACE_PATH()
{
			//QueryFaceFlags face;
			//int ret=HA_QueryFaceID(cam,&face,1,1,1);
			//printf("ddddddd\n");
			//if(ret==0){
			//	printf("name=%s Id=%s\n",face.personName,face.personID);
			//}
			/**/
			int ret;
			int Num=4;
			char* patch[5] = { NULL };
			int i = 3;
			char patchbuf[25];
			sprintf(patchbuf, "./%d.jpg", i);
			patch[0] = patchbuf;
			FaceFlags faceID;
			sprintf(faceID.faceID, "%s_%d", "test_id", i); //人员ID
			sprintf(faceID.faceName, "%s_%d", "test_name", i);//
			sprintf(faceID.userParam, "%s", "test_data--------------------");//人员姓名

			faceID.role = 1;//人员角色，0：普通人员。 1：白名单人员。 2：黑名单人员。 -1：所有人员。
			faceID.wgCardNO = 12;//韦根协议门禁卡号
			faceID.effectTime = 0xFFFFFFFF;
			faceID.effectStartTime = (unsigned int)make_time(2019, 1, 1, 0, 0, 0);
		
			ret = HA_AddJpgPaths(cam, &faceID, patch, 1, 1);
			if (ret != 0) {
				printf("%s 注册失败 ret=%d\n", patchbuf, ret);
			}
			//printf("注册进度>>>:%.3f\n", (i + 1) / (float)Num * 100);
			/*
			for(int i=0;i<Num;i++){
				char* patch[5]={NULL};
				char patchbuf[25];
				sprintf(patchbuf,"./%d.jpg",i);
				patch[0]=patchbuf;
				FaceFlags faceID;
				sprintf(faceID.faceID, "%s_%d", "test_id",i); //人员ID
				sprintf(faceID.faceName, "%s_%d", "test_name",i);//人员姓名
				faceID.role = 1;//人员角色，0：普通人员。 1：白名单人员。 2：黑名单人员。 -1：所有人员。
				faceID.wgCardNO = 12;//韦根协议门禁卡号
				faceID.effectTime = 0xFFFFFFFF;
				faceID.effectStartTime = (unsigned int)make_time(2019, 1, 1, 0, 0, 0);

				//有效期截止时间，该人员信息在该时间内有效,从1970年1月1日0时0分0秒到截止时间的秒数（0xFFFFFFFF表示永久有效，0表示永久失效） 最大2038 年
				//有效期起始时间，该人员信息在该时间之后有效,从1970年1月1日0时0分0秒到起始时间的秒数（0表示未初始化） 最大2038 年
				sprintf(faceID.userParam, "%s", "sssssssssssssssss"); //char*[68]用户自定义文本内容，可用于相机TTS播放、LCD显示，也可作为用户平台自定义属性使用 
				ret=HA_AddJpgPaths(cam,&faceID,patch,1,1);
				if (ret != 0) {
					printf("%s 注册失败 ret=%d\n",patchbuf, ret);
				}
				printf("注册进度>>>:%.3f\n",(i+1)/(float)Num*100);
			}
			*/
			printf("注册完成\n");
			return 0;
}

/*
 * @brief   取得sdk版本
 * @param   version[out] sdk版本信息
 * @return  版本号    【返回值固定3】

 struct HaSdkVersion
{
	sdk_version//sdk版本protocl_version//协议类型sdk_code_version
	//sdk源代码版本min_firmware_ver//支持的最低固件版本algorithm_version//sdk使用得算法版本
};
 */
//HASDK_API int HASDK_CALL HA_GetVersion(struct HaSdkVersion* version);
void HA_GET_SDK_VERSION()
{
	printf("HA_GET_SDK_VERSION \n");
	HaSdkVersion sdkVersion;
	HA_GetVersion(&sdkVersion);
	//sdk_version//sdk版本protocl_version//协议类型sdk_code_version
	//sdk源代码版本min_firmware_ver//支持的最低固件版本algorithm_version//sdk使用得算法版本
	printf("sdk_version=%s \n", sdkVersion.sdk_version);
	printf("protocl_version=%s \n", sdkVersion.protocl_version);
	printf("sdk_code_version=%s \n", sdkVersion.sdk_code_version);
	printf("min_firmware_ver=%s \n", sdkVersion.min_firmware_ver);
	printf("algorithm_version=%s \n", sdkVersion.algorithm_version);
}

void receiveData(const uint8_t* receive_pb, int pb_length)
{
	pb_istream_t istream = pb_istream_from_buffer(receive_pb, (size_t)pb_length);
	bool eof = false;
	uint32_t tag = 99;
	pb_wire_type_t write_type = PB_WT_VARINT;
	pb_decode_tag(&istream, &write_type, &tag, &eof);
	int messageType = (int)tag;
	int result = -1;
	bool decode_status;
	SendDataBack photoId = SendDataBack_init_zero;
	switch (messageType)
	{
		//case MsgType_SendDataBack_tag:
		//	printf("server receive tag=NZ_MESSAGE_SocketTag_GetVersion_tag \n");
		//	break;
	case MsgType_AddFcae_tag:
		printf("server receive tag=MsgType_AddFcae_tag\n");
		result=HA_ADD_FACE_REQ(&istream);
		if (result >= 0)
		{
			HA_ADD_FACE_PATH();
		}
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
		printf("sendMessaage Success deiceID=%s  SeriNum=%d\n", photoId.Id.dev, photoId.SeriNum);
		break;
	case MsgType_OperationFaceId_tag:
		printf("server receive tag=MsgType_OperationFaceId_tag\n");
		HA_QUERY_FACEID(&istream);
		
		break;
	default:
		printf("server receive tag= ERROR\n");
		break;
	}
}

void* recvsocket(void* arg)//接收server端socket数据的线程
{
	int st = *(int*)arg;
	//char s[512];
	uint8_t undecode_buf[512];
	while (1)
	{
		//memset(s, 0, sizeof(s));
		memset(undecode_buf, 0, sizeof(undecode_buf));
		int rc = recv(st, undecode_buf, sizeof(undecode_buf), 0);
		printf("client receive Return rc=%d\n", rc);
		if (rc <= 0)//如果recv返回小于等于0，代表socket已经关闭或者出错了
		{
			close(sock_fd);
			isConnect = false;
			sock_fd = -1;
			printf("Server Break rc=%d\n", rc);
			//ha_Exit(0);
			break;
		}
		receiveData(undecode_buf, rc);

	}
	return NULL;
}
int socket_start()
{
	struct sockaddr_in server_addr;
	int sock_ = socket(AF_INET, SOCK_STREAM, 0);//初始化socket
	if (sock_ == -1) {
		printf("sock_==-1%s\n", strerror(errno));
		return -1;
	}
	bzero(&server_addr, sizeof(server_addr));//编辑服务端地址信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(Port);
	//server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (!inet_aton("192.168.2.219", &server_addr.sin_addr))
	{
		printf("bad address");
	}
	int tmp = connect(sock_, (struct sockaddr*)(&server_addr),
		sizeof(struct sockaddr));//连接服务端socket
	if (tmp == -1) {
		printf("connect error===%s\n", strerror(errno));
		return -1;
	}
	isConnect = true;
	return sock_;
}
int HA_INIT()
{
	HA_LogEnable(1);
	HA_Init();
	int err = 0;
	HA_SetNotifyConnected(1);
	HA_InitFaceModel(NULL);
	HA_RegConnectEventCb(ServerConnectEventCb, 0);
	printf("inited\n");
	cam = HA_Connect("192.168.2.55", 9527, NULL, NULL, &err);
	//192.168.202.140
	printf("erro=%d\n", err);
	if (cam == NULL) {
		printf("连接失败\n");
		return-1;
	}
	HA_RegFaceRecoCb(cam, getting_face, NULL);
	printf("HA_RegFaceRecoCb finish\n");
	return 0;
}

int main(int argc,char** argv){

	int choose = -1;
	char useChars[16] = "test_id_1";
	int sleepTime = 5;
	signal(SIGINT,ha_Exit);
	//sleep(60);
	HA_INIT();
	SystemTime sysTime = { 0 };
	
	pthread_t receiveThread;
	while (1)
	{
		if (sock_fd < 0)
		{
			sock_fd = socket_start();
			printf("sock_fd==%d   sleepTime=%d\n", sock_fd, sleepTime);
			if (sock_fd > 0)
			{
				pthread_create(&receiveThread, NULL, recvsocket, &sock_fd);
				pthread_join(receiveThread, NULL);
			}
			if(sleepTime<60)
			sleepTime++;
		}
		sleep(sleepTime);
		printf("循环sock_fd==%d   sleepTime=%d\n", sock_fd, sleepTime);
	}
	//printf("1\n");
	
	//printf("2\n");
	

	/*
	do{
		printf("请输入操作编码:");
		while(scanf("%d", &choose) != -1)
		{
			
			switch (choose)
			{
			case 0:
				//HA_RegFaceRecoCb(cam, getting_face, NULL);
				HA_GET_SDK_VERSION();
				break;
			case 1:
				HA_ADD_FACE_PATH();
				break;
			case 2:
				HA_DELETE_FACEID(useChars);
				printf("HA_DELETE_FACEID finish \n");
				break;
			case 3:
				HA_LCD_DISPLAY();
				//printf("HA_DELETE_FACEID finish \n");
				break;
			default:
				break;
			}
			printf("请输入操作编码:");
		}
	}while(0);
	*/
	
	
}
