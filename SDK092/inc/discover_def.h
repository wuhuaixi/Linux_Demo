#ifndef IPSCAN_DEF_H
#define IPSCAN_DEF_H


#define MCAST_PORT 6100
#define MCAST_IP_D "224.0.1.1"

#define  MSG_PACKET_PROGRESS				3001
#define  MSG_PACKET_ADVANCE					3002
#define  MSG_PACKET_CMCAST					3003
#define  MSG_PACKET_CMCAST_ACK				3004
#define  MSG_PACKET_IPSET                   3005

struct ipscan_t
{
    char mac[20];  //mac��ַ
    char ip[20];   //ip��ַ
    char netmask[20];  //����
    char manufacturer[16];  //������
    char platform[32];  //ƽ̨
    char system[32];    //ϵͳ
    char version[64];   //�汾��Ϣ
};

struct ipset_t
{
    char mac[20];
    char ip[20];
    char netmask[20];
    char gateway[20];
};

#if defined(WIN32) || defined(WIN64)
    #define HASDK_CALL __stdcall
#else
    #define HASDK_CALL
#endif

typedef void (HASDK_CALL *discover_ipscan_cb_t)(const struct ipscan_t* ipscan, int usr_param);

#endif

