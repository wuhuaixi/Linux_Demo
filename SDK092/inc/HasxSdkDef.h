//#pragma once
#ifndef HASX_SDK_DEF_H
#define HASX_SDK_DEF_H

// ������

struct CamCtrlLED
{
    int seq;
    int lightType;
    int hz;
    int trigType;
    int phase;
    int pulseWidth;

    int rev[32];
};


struct CamCtrlAutoCtrl
{
    int standard;
    int maxShut;
    int minShut;
    int maxGain;
    int gainLevel[4];

    int agcSelect[6]; //16*12 ��һ���ض�Ӧһ������31-0˳������

    int rev[32];
};

struct CamCtrlMannualCtrl
{
	int manualShut;
	int mannuGainLevel;
	int mannualGainValue;
	int mannualR;
	int mannualGr;
	int mannualGb;
	int mannualB;
	int mannualRoft;
	int mannualGroft;
	int mannualGboft;
	int mannualBoft;
	int rev[32];
};

struct CamCtrlImageEnhance
{
    int imgSaturability; //���Ͷ�
    int imgContrast; //�Աȶ�
    int imgSharpen; //��
    int imgNoise; //����
    int imgGamma;
    int imgGammaEnable;
    int rev[31];
};
struct CamCtrlTrigIO
{
    int trigType; //0-�������� 1-�����ش����� 2-�½��ش����� 3-�������½�������
    int trigNum;  //���Ϊ3
    int trigInter[2]; //ms
    int flashEable;  //�Ƿ�����
    int flashIndex;  //���ĸ���

    int rev[8];
};


struct CamCtrlExtSync
{
    int enable;
    int phase;
    int filter;
};

struct CamCtrl
{
    int enableAutoExp;
    int enableAutoAwb;
    struct CamCtrlAutoCtrl autoCtrl;
    struct CamCtrlMannualCtrl manualCtrl;
    struct CamCtrlImageEnhance imgEnhance;
    struct CamCtrlLED led[5];
    struct CamCtrlTrigIO trigIO[8];
    struct CamCtrlExtSync extSync;

    int jpegQ;
    int h264W;
    int h264H;
    int h264Bitrate;

    int ip;
    int netmask;
    int gateway;

    int systime; //unix time

	unsigned short trig_shut;
	unsigned short trig_gain;

    int sensorType; // 0 CCD, 1 CMOS

	int rev[126];
};

struct DayTime
{
    unsigned char startHour;
    unsigned char startMinute;
    unsigned char endHour;
    unsigned char endMinute;
};
#endif




