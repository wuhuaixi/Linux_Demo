#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> //mkdir声明
#include <dirent.h>
#include <pthread.h>
#include <getopt.h>
#include <unistd.h>
#include <iostream>
using namespace std;
#include "HASdk.h"


int main(int argc,char *argv[])
{
	if (1) {
		
		char *patch = argv[1];
		patch="2.jpg";
		string jpg(patch);
		string jpg_face;
		string jpg_twist;
		unsigned char face[70 * 1024];
		unsigned char twist[70 * 1024];
		unsigned char jpgbuf[70 * 1024];
		unsigned int jpg_len=0;
		memset(face, 0, 70 * 1024);
		memset(face, 0, 70 * 1024);
		memset(jpgbuf, 0, 70 * 1024);
		int face_len;
		int twist_len;
		int w;
		int h;
		string face_orig(patch);
		printf("patch=%s \n",patch);
		int point=jpg.find_last_of(".");
		jpg_face =jpg.replace(point,1,"_face.");
		jpg = patch;
		jpg_twist = jpg.replace(point, 4, "_twist.bmp");
		HA_InitFaceModel(NULL);
		int ret=HA_GetJpgPathFeatureImage((unsigned char*)face_orig.c_str(),twist,&twist_len,&w,&h, face,&face_len);
		if (ret == 0) {
			ret=HA_SaveJpg(jpg_face.c_str(), face, face_len);
	
			FILE* p=fopen(jpg_twist.c_str(), "wb");
			if (p == NULL) {
				return -1;
			}
			int fret=fwrite(twist, twist_len, 1, p);
			fclose(p);
			if (ret != 0||fret<1) {
					printf("save error ret=%d\n", ret);
					return -1;
			}
			else {
					printf("save succeed\n");
			}
		}
		else{
			printf("GetFaceFeature Error  ret=%d\n",ret);
			return -1;
		}
	}
	else {
		printf("file name can not NULL\n");
		return -1;
	}
    return 0;
}

