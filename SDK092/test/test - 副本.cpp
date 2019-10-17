#include <stdio.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "HASdk.h"
using namespace std;

HA_Cam* cam=NULL;
void ha_Exit(int signo){
	printf("[info]exit>>>>>\n");
	 HA_DeInit();
	printf("[sucess]exit>>>>>\n");
	_exit(1);	
}



void HASDK_CALL DecodeImageCb(struct HA_Cam* cam, unsigned char* rgb, int width, int height, int usrParam){
	printf("w=%d,h=%d\n",width,height);
	
}


int Connected=0;

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


 void HASDK_CALL getting_face(struct HA_Cam* cam, const struct FaceRecoInfo* faceRecoInfo, void* usrParam){
	printf("获取到人脸 name=%s id=%s role=%d\n",faceRecoInfo->matchPersonName,faceRecoInfo->matchPersonId,faceRecoInfo->matchRole);
	
	if(faceRecoInfo->existImg !=0){
		FILE* fp = fopen("./face.jpg","wb");
		if(!fp){
			printf("fopen error \n");
			return;
		}
		int ret = fwrite(faceRecoInfo->img,1,faceRecoInfo->imgLen,fp);
		printf("ret = %d \n",ret);
		fclose(fp);
	} else {
		printf("faceRecoInfo->existImg =0 \n");
	}
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

int main(int argc,char** argv){
	signal(SIGINT,ha_Exit);
	HA_Init();
	int err=0;
	HA_SetNotifyConnected(1);
	printf("inited\n");
	cam=HA_Connect("127.0.0.1",9527,NULL,NULL,&err);
	//192.168.202.140
	printf("erro=%d\n",err);
	HA_InitFaceModel(NULL);
	HA_RegConnectEventCb(ServerConnectEventCb,0);
	if(cam==NULL){
		printf("连接失败\n");
		return-1;
	}
	int error=-1;
	do{
		HA_RegFaceRecoCb(cam, getting_face,NULL);
		
		/*
		QueryFaceFlags face;
		int ret=0;//HA_QueryFaceID(cam,&face,1,1,1);
		printf("ddddddd\n");
		if(ret==0){
			printf("name=%s Id=%s\n",face.personName,face.personID);
		}
		int Num=3;
		for(int i=0;i<Num;i++){
			char* patch[5]={NULL};
			char patchbuf[25];
			sprintf(patchbuf,"./jpg/(%d).jpg",i);
			patch[0]=patchbuf;
			FaceFlags faceID;
    		sprintf(faceID.faceID, "%s_%d", "test_id",i);
    		sprintf(faceID.faceName, "%s_%d", "test_name",i);
    		faceID.role = 1;
    		faceID.wgCardNO = 12;
    		faceID.effectTime = (unsigned int)make_time(2019,1,1,0,0,0);
			ret=HA_AddJpgPaths(cam,&faceID,patch,1,1);
			if (ret != 0) {
				printf("%s 注册失败 ret=%d\n",patchbuf, ret);
			}
			printf("注册进度>>>:%.3f\n",(i+1)/(float)Num*100);
		}
		printf("注册完成\n");
		
		*/
		while(1){
			sleep(2);
		}
	}while(0);
}
