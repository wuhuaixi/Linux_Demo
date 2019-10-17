/*
 * config_gw.h
 *
 *  Created on: 2014年7月4日
 *      Author: chens
 */

#ifndef CONFIG_GW_H_
#define CONFIG_GW_H_

#include <string.h>
#include <stdio.h>

#define MAX_LANE_NUM    (4)
#define MAX_FLASH_NUM   (4)
#define MAX_RADAR_NUM   (4)
#define MAX_INPUT_IO_NUM    (8)
#define MAX_COIL_GROUP  (4)
#define  MAX_CABINET_STATE (8)

#define HA_SERIA_RS485 (1) 
#define HA_SERIA_RS232 (2)

//人员查询条件标记
typedef enum {
  //通过ID查询
  QUERY_BY_ID = 0x1,

  //通过姓名查询
  QUERY_BY_NAME = 0x2,

  //通过韦根卡号查询
  QUERY_BY_WGNO = 0x4,

  //通过有效期截止时间范围查询
  QUERY_BY_EFFECT_TIME = 0x8,  

  //通过有效期起始时间范围查询
  QUERY_BY_EFFECT_START_TIME = 0x10
}ConditionFlag;



// 记录查询条件标记。
enum RecordQueryFlag {
  /*! 通过抓拍时间范围查询。 */
  RECORD_QUERY_FLAG_TIME         = 0x1,

  /*! 通过比对分数范围查询。 */
  RECORD_QUERY_FLAG_SCORE        = 0x1 << 1,

  /*! 通过性别查询。 */
  RECORD_QUERY_FLAG_SEX          = 0x1 << 2,

  /*! 通过年龄范围查询。 */
  RECORD_QUERY_FLAG_AGE          = 0x1 << 3,

  /*! 通过比上的人员id查询。 */
  RECORD_QUERY_FLAG_ID           = 0x1 << 4,
  
  /*! 通过比上的人员姓名查询。 */
  RECORD_QUERY_FLAG_NAME         = 0x1 << 5,

  /*! 通过抓拍图像的人像质量范围查询。 */
  RECORD_QUERY_FLAG_QVALUE       = 0x1 << 6,

  /*! 通过记录上传状态查询。 */
  RECORD_QUERY_FLAG_UPLOAD       = 0x1 << 7,

  /*! 通过记录数据库编号查询。 */
  RECORD_QUERY_FLAG_SEQUENCE     = 0x1 << 8
};

//人员查询条件标记
typedef enum {
  //精确查询
  QUERY_EXACT = 0x0,

  //模糊查询
  QUERY_FUZZY = 0x1
}QueryMode;

/// 比对模式。
enum MatchMode {
	/*! 未初始化。*/
	MATCH_MODE_NULL        = 0,

	/*! 对应--刷脸开闸功能。 */
	MATCH_MODE_NORMAL      = 1,

	/*! 对应--刷身份证开闸功能。 */
	MATCH_MODE_IDCARD_1TO1 = 2,

	/*! 对应--刷脸+刷身份证开闸功能。 */
	MATCH_MODE_FACE_IDCARD  = 3,

	/*! 对应--刷卡开闸功能。 */
	MATCH_MODE_WGCARD      = 4,

	/*! 对应--刷脸+刷卡开闸功能。 */
	MATCH_MODE_FACE_WGCARD = 5,

	/*! 对应--过人开闸功能。 */
	MATCH_MODE_ANY_FACE    = 6,

	/*! 对应--刷脸+白名单开闸功能 或者刷卡+白名单开闸功能*/
	MATCH_MODE_NORMAL_OR_WGCARD = 7,

	 /*! 对应--刷脸或刷身份证。 */
	MATCH_MODE_NORMAL_OR_IDCARD_1TO1 = 8,

	/*! 对应--刷卡并截图 */
	MATCH_MODE_IDCARD_SNAPSHOT       = 9,

	/*! 对应--刷脸或（刷脸+刷身份证） */
	MATCH_MODE_NORMAL_OR_FACE_IDCARD = 10,

	/*! 对应--刷脸或RFID全景快照。 */
	MATCH_MODE_NORMAL_OR_SNAPSHOT    = 20


};

/// gpio输入方式。
enum GpioInType{   
  /*! 韦根26协议。 */
  IN_STATE_WG26  = 0,
  
  /*! 韦根34协议。 */
  IN_STATE_WG34  = 1,

  /*! 韦根36协议。 */
  IN_STATE_WG36  = 2,

  /*! 韦根44协议。 */
  IN_STATE_WG44  = 3,

  /*! 韦根66协议。 */
  IN_STATE_WG66  = 4,
  
  /*! IO输入方式。 */
  IN_STATE_IO = 255
};
    

/// 图片形式。
typedef enum {
  /*! 未初始化数据输出模式。 */
  IMAGE_FORM_NULL    = 0,

  /*! 全景。 */
  IMAGE_FORM_OVERALL = 0x1,

  /*! 特写。 */
  IMAGE_FORM_CLOSEUP = 0x1 << 1,

  /*! 全景+特写。 */
  IMAGE_FORM_BOTH    = IMAGE_FORM_OVERALL | IMAGE_FORM_CLOSEUP
} ImageForm;

/// 输出选项。
enum OutputOption {
  /*! 选项为空。 */
  OUTPUT_OPTION_NULL      = 0,

  /*! 全景图。 */
  OUTPUT_OPTION_OVERALL   = IMAGE_FORM_OVERALL,

  /*! 特写图。 */
  OUTPUT_OPTION_CLOSEUP   = IMAGE_FORM_CLOSEUP,

  /*! 比对原型图。 */
  OUTPUT_OPTION_PROTOTYPE = 0x1 << 2,

  /*! 特征数据。 */
  OUTPUT_OPTION_FEATURE   = 0x1 << 3,

  /*! 调试图像(用于算法调试)*/
  OUTPUT_OPTION_TWIST_IMAGE = 0x1 << 4
};

/// 人脸功能选项。
enum FuncOption {
  /*! 除抓拍功能（必不可少）外的无其它功能选项。 */
  FUNC_OPTION_NULL       = 0,

  /*! 人脸比对。 */
  FUNC_OPTION_MATCH      = 0x1,

  /*! 年龄检测。 */
  FUNC_OPTION_AGE        = 0x1 << 1,

  /*! 性别检测。 */
  FUNC_OPTION_SEX        = 0x1 << 2,

  /*! 表情检测。 */
  FUNC_OPTION_EMOTION    = 0x1 << 3,

  /*! 肤色检测。 */
  FUNC_OPTION_SKIN       = 0x1 << 4,

  /*! 活体检测。 */
  FUNC_OPTION_ALIVE      = 0x1 << 5,

  /*! 安全帽检测。 */
  FUNC_OPTION_HAT        = 0x1 << 6

};

/// 数据上传模式。
typedef enum {
  /*! 未初始化。 */
  UPLOAD_MODE_NULL = 0,

  /*! TCP协议上传。 */
  UPLOAD_MODE_TCP  = 1,

  /*! FTP协议上传。 */
  UPLOAD_MODE_FTP  = 2,

  /*! HTTP协议上传。 */
  UPLOAD_MODE_HTTP = 3,

  /* WebService上传*/
  UPLOAD_MODE_SERVICE=4
} UploadMode;





/// 韦根协议格式定义。
typedef enum {
  WG26 = 0,

  WG34 = 1,

  WG36 = 2,

  WG44 = 3,

  WG66 = 4,
  
  GPIO = 255
} WiegandType;

typedef enum {
  //无任何操作
  HA_SYNC_NONE = 0,
  
  //添加人员信息
  HA_FACE_ADD = 1,

  //修改人员信息
  HA_FACE_UPDATE = 2,

  //删除人员信息
  HA_FACE_DEL = 3
}FaceSyncMode;


enum PTZCTL {
 PTZ_CTRL_ZOOM_IN    =5,  /*! 变倍（放大）*/
 PTZ_CTRL_ZOOM_OUT   =6,  /*! 变倍（缩小）*/
 PTZ_CTRL_FOCUS_IN   =7, /*! 聚焦（拉近）*/
 PTZ_CTRL_FOCUS_OUT  =8 /*! 聚焦（拉远）*/
};

enum PTZMODE {
PTZ_MODE_ONCE   =1,    /*! 一次运动*/
PTZ_MODE_START  =2,   /*! 启动*/
PTZ_MODE_STOP   =3    /*! 停止*/
};





struct config_size {
    unsigned short width;
    unsigned short height;
};

struct config_point
{
    unsigned short x;
    unsigned short y;
};

struct config_rect {
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
};


/******* 控制系统工作时间及其校验与默认设置 ********/

struct config_worktime {
    unsigned char start_hour;
    unsigned char start_min;
    unsigned char end_hour;
    unsigned char end_min;
};


/****** 地址信息的配置、校验、重置  ******/

struct config_addr {
    char device_id[32];
    char device_name[32];
    char addr_id[32];
    char addr_name[96];
    char direction_id[32];
    char direction_name[96];

    unsigned short lane_number; /* 车道数目 */
    unsigned short lane_start_id; /* 车道起始编号 */

    unsigned char match_light[MAX_LANE_NUM]; /* 车道与车灯关联 */

    char master_mode;   /* 主检测模式 */
    char slave_mode;    /* 从检测模式 */
    char mode_change_threshold; /* 模式切换时阈值, 设置主模式多少次未检测时切换到从模式 */

    unsigned char serial_index;
    int serial_baudrate;   // 波特率
    unsigned char serial_databit;    // 数据位
    unsigned char serial_parity; // 是否开始校验
    unsigned char serial_stopbit;    // 停止位

    char resv[113];
};


/****** 线圈卡口的配置、校验、重置  ******/

/* 用来配置某个input io的具体属性 */
struct coil_io_attr {
    unsigned char group; /* 所属线圈的组号(车道号) < MAX_COIL_GROUP */
    unsigned char index; /* 属于该组线圈的第几个IO信号 0 or 1 */
    unsigned char count; /* 触发多少张 <= 2 */
    unsigned char match_light;/* 闪光灯关联，低四位每一位(=1)表示关联该路闪光灯 */
};

struct config_coil {
    int enable;
    unsigned int distance;/* 两线圈之间距离,单位cm 用来计算两个IO之间时间差 */
    struct coil_io_attr io_attr[MAX_INPUT_IO_NUM];

    char resv[64];
};


/****** 雷达卡口的配置、校验、重置 ******/

enum RADAR_TYPE {
    RADAR_TYPE_NONE = 0, RADAR_TYPE_CSRIN = 1, RADAR_TYPE_CSRIN_M = 2
};

struct config_radar {
    int enable;

    enum RADAR_TYPE type;

    /* 总共有多少个雷达 */
    unsigned int count;

    /* 雷达与车道匹配，如match_lane[0] = 2，就表示第一个雷达对应车道2 */
    unsigned char match_lane[MAX_RADAR_NUM];

    /* 雷达与闪光灯匹配，match_light的下标n加上1表示雷达序号（从1开始）
     * match_light[n]所对应的值表示所对应的闪光灯
     * 0x1 0x2 0x4 0x8 分别表示 1、2、3、4路闪光灯 0x3则表示1、2路同时闪
     * 0x0表示不闪灯
     */
    unsigned char match_light[MAX_RADAR_NUM];

    /* 是否将雷达数据记录到日志(通过网络发送) */
    int enable_log;

    char resv[64];
};

/****** 视频卡口参数的配置、校验、重置******/

enum CALC_LANENO_METHOD {
    LEFT_TO_RIGHT, // 画面最左边作为起始车道1
    RIGHT_TO_LEFT
};


/****** 视频卡口参数的配置、校验、重置******/

enum vdetect_type {
    VDETECT_TYPE_RECO,  /* 使用车牌识别检测车辆 */
    VDETECT_TYPE_DET,   /* 使用视频检测检测车辆 */
    VDETECT_TYPE_BOTH   /* 以上两个同时使用 */
};

struct config_vdetect {
    int enable; /* 视频检测使能 */

    enum vdetect_type type;

    int flash; /* 视频触发闪光 */
    int motion; /* 运动检测 */
    int diff; /* 差分使能 */
    struct config_rect detect_area; /* 视频检测区域 */
    struct config_rect virtual_coil; /* 虚拟线圈，触发区域 */

    int night_threshold;    /* 白天晚上亮度 阈值 */
    int rsv2;

    unsigned skip; /* 跳帧数，车辆触发以后跳过多少帧不检测 */
    unsigned cut; /* 上沿切割像素 */
    unsigned min_size;
    unsigned max_size;
    unsigned resize;
    float step;

    int debug; /* 调试开关，控制是否传输调试图像 */
    int draw_coil; /* 将虚拟线圈绘制在调试图像上 */
    int draw_area; /* 将检测到的车辆区域绘制在调试图像上 */

    enum CALC_LANENO_METHOD m;

    /* 与闪光灯匹配，match_light的下标n加上1表示雷达序号（从1开始）
     * match_light[n]所对应的值表示所对应的闪光灯
     * 0x1 0x2 0x4 0x8 分别表示 1、2、3、4路闪光灯 0x3则表示1、2路同时闪
     * 0x0表示不闪灯
     */
    unsigned char match_light[MAX_LANE_NUM];

    struct config_point virtual_coil_polygon[4];

    char resv[40];
};


/****** 人脸检测参数的配置、校验、重置 ******/
struct config_face_detect {
    int enable;
    int debug; /* 是否发送调试图像等 */
    struct config_rect detect_area; /* 从原图上取一部分进行检测 */
    struct config_size minsize; /* 指定检测图上人脸所占像素范围 */
    struct config_size maxsize;
    float step; /* 每次检测步进比例 */

    float ratio; // 从原来预留的64字节中取出一点
    unsigned interval; /* 跳帧数 */

    unsigned use_motion;    /* 使用运动检测进行抓拍 */

    unsigned face_step; /* 在运动检测的基础上,隔多少次检测一次人脸 */

    char resv[48]; /* 预留 */
};

/* 根据颜色过滤车牌 */
enum reco_filter_color {
    RECO_FILTER_BLUE = 0,
    RECO_FILTER_BLACK = 1,
    RECO_FILTER_YELLOW = 2,
    RECO_FILTER_WHITE = 3,
    RECO_FILTER_GREEN = 4
};

enum reco_filter_num {
    RECO_FILTER_NULL = 0,  
    RECO_FILTER_XUE = 1,
    RECO_FILTER_JING = 2 
};

/****** 识别参数的配置、校验、重置 ******/
struct config_reco {
    int enable;
    float ratio;
    char province[16];

    unsigned short min_width;
    unsigned short max_width;

    struct config_rect reco_area[MAX_LANE_NUM];

    int draw_reco_area; /* 在识别结果上画出识别区域 */

    unsigned int filter_color;
    unsigned int filter_num;

    unsigned short same_plate_report_time; //相同车牌上报间隔，单位:秒

    unsigned char draw_reco_area_video;

    unsigned char reco_mode; //0,1为正常角度，2为自动，3为大角度

    char resv[48];
};


/****** 特殊需求的配置、校验、重置 */

enum PLATE_FILTER_TYPE {
    PLATE_FILTER_TYPE_NONE = 0,
//  DROP_NO_PLATE,
//  ONLY_KEEP_BLUE,
//  ONLY_KEEP_YELLOW,
//  DROP_YELLOW,
//  DROP_BLUE
};

struct config_special {
    int merge_two; /* 当结果有两张时进行合并 */
    int keep_one; /* 没超速只保留一张图片 */
    enum PLATE_FILTER_TYPE plate_filter; /* 过滤特定条件的车牌 */

    char resv[32];
};

/****** 限速与抓拍相关的配置、校验、重置  ******/

struct config_limit_speed {
    /* 抓拍张数与抓拍间隔 */
    unsigned short capture_count;
    unsigned short overspeed_count;
    unsigned int interval;

    unsigned short lspeed[MAX_LANE_NUM];  // 车道标定限速值
    unsigned short rlspeed[MAX_LANE_NUM]; // 超速处理的限速值

    char resv[32];

};

struct searchCamInfo{
	/*! 设备序列号。 */
	char devId[32];
	char devIp[16];
	unsigned int port;
	/*! 点位编号。 */
	char addr_id[32];
	/*! 点位名称。 */
	char addr_name[96];

};

struct WifiSignal {
	char ssid[36]; 				// wifi名称
	unsigned int frequency;		// 频率 2.4G或5G
    int rssi;   				// 信号强度 信号强度在[-126, 0]范围递增，频率为5G时[156, 200)递增
    char mac[20];  				// MAC地址
    char encryptMethod[256];	// 加密方式
    int speed;					// 连接速度
};

struct config_net {
    UploadMode upload_mode;
    char ftp_server[16];
    char tcp_server[16];
    char ntp_server[16];
    int ntp_interval;
    unsigned short ftp_port;
    unsigned short tcp_port;
    char ftp_user[32];
    char ftp_passwd[32];

    char led_server[16];
    unsigned short led_port;

    unsigned short http_port;
    char http_server[16];

    char tcp_enable;
    char ftp_enable;
    char led_enable;
    char http_enable;

    char resv[88];
};

struct CONF_OSD    // 文字叠加
{
    unsigned short imgStartX;                    // 文字起始位置X坐标
    unsigned short imgStartY;                    // 文字起始位置Y坐标

    // ToDo: add for single and composed image
    unsigned char imgFontSize;                  // 文字大小
    unsigned char imgFontColor[3];              // 文字颜色（RGB）

    char imgOSDRules[512];                      // utf-8

    char resv[16];                              // 保留
};


struct lamp_area
{
    int lamp_num; //2灯or3灯

    unsigned short only_red_x;
    unsigned short only_red_y;
    unsigned short only_red_w;
    unsigned short only_red_h;

    unsigned short all_lamp_x;
    unsigned short all_lamp_y;
    unsigned short all_lamp_w;
    unsigned short all_lamp_h;
};

struct config_people_red
{
    int enable;
    struct lamp_area lamp;

    char resv[64];

};


struct config_gw_park {
    unsigned char offline; // 1为离线，0为在线, 2为自动（即脱机检查）
    unsigned char alarm_out_mode; //0为白名单开，1为过车开
    unsigned char transfer_offline_data; //上传离线数据
    unsigned char diable_serial_output;  //中断/恢复原本设备控制的串口输出，透明串口输出不在此控制

    unsigned char same_count; // 模糊匹配车牌阀值
    unsigned char min_volume; //最小音量
    unsigned char max_volume; //最大音量
    unsigned char cur_volume; //当前音量

    unsigned char light;

    unsigned char drive_direct; //0:全抓, 1:只抓车头，2只抓车尾

    unsigned char ctrl_light_mode; //0常亮，1智能控灯使能，2常闭，3线圈闪光模式
    unsigned char day_brightness; //白天亮度阀值
    unsigned short alarmOutDuration; //自动开闸时间间隔(500-5000ms)
    unsigned char disable_io_port;  //中断GPIO控制
    unsigned char disable_io_output; //中断/恢复原本设备控制的继电器、电平输出
    unsigned char gpio_in;  //GPIO IN使能，bit[7-0]对应gpio[7-0]
    unsigned char gpio_out; //GPIO OUT使能，bit[7-0]对应gpio[7-0]
    unsigned char flash_sync_out1;//同步输出out2
    unsigned char reboot_flag; //0-每天自动重启，1-重不重启
    unsigned char resv[16]; //备用
};

/****** 卡口整体配置  ******/

/*
 * @brief   magic_number    配置修改记录
 *      3   2014-10-22 添加人脸检测相关参数, 每个配置预留空间
 *      4   2014-12-09 添加视频卡口检测相关参数
 *      5   2015-01-07 卡口添加白天晚上阈值, 调试图像协议进行了微调
 *      6   2015-01-21 在识别的配置中添加车牌颜色过滤和车牌号码过滤
 *      7   2015-06-16 加入行人闯红灯配置
 */
//static const int magic_number = 7;

//是否交替控灯
struct config_carbinet_inturn_control
{
    int isEnable; //是否有效 0无效 1有效
    char ip[64];  //IP地址
};
struct MessageCarPortState
{
    int carPortState; //状态 0 无车 1有车 2 压线 3 特殊车位
    int lightColor;   //颜色
    int laneNum;  //当前有几根车道
    int   hasCar[MAX_LANE_NUM];   //每个位置是否有车
    int   hasPlate[MAX_LANE_NUM]; //是否有车牌
    char  plate[MAX_LANE_NUM][16]; //车牌号码
}; 

//车位信息
struct config_carbinet
{
    int isSpecial; //是否特殊车位 0一般车位 1特殊车位
    int portNum;   //车位号
};


//车位状态信息
struct config_carbinet_state
{
    int isEnable; //是否有效  0无效 1有效
    int isFlicker;//是否闪烁  0不闪 1闪
    int lightColor;//灯的颜色 0灭 1红 2绿 3黄 4蓝色 5品红 6青 7白
};


//车位相机算法配置
struct config_carbinet_vdetect
{
    config_point inventedRoi[MAX_LANE_NUM][4];//虚拟线圈
};

//车位相机整体配置信息
struct config_gw_car_port
{
    //控灯模式  1内置灯 2 外置灯 3 内加外
    int lightControlMode;
    //交替控灯
    struct config_carbinet_inturn_control inturnControl;
    //车位状态配置
    struct config_carbinet_state carbinetState[MAX_CABINET_STATE];
    //车位配置信息
    struct config_carbinet carbinet[MAX_LANE_NUM];
    //车位相机算法配置
    struct config_carbinet_vdetect alg;
};


struct config_http
{
    char http_ip[20];
    unsigned short http_port;
    unsigned short ssl_port;

    int timeout;

    unsigned char enable_ssl;
    unsigned char enable_reg;
    unsigned char enable_post_vehicle;
    unsigned char enable_img;
    unsigned char enable_plate_img;

    unsigned char enable_post_io_info;
    unsigned char enable_post_serial_data;

    unsigned char vehicle_level;

    char reg_url[96];
    char post_vehicle_url[96];
    char post_ioinfo_url[96];
    char post_serial_url[96];

    unsigned char resv[128];
};

struct device_group_cam_attr
{
    char ip[20];
    char cam_name[32];
    char assistFlag;
    char inFlag;
    char resv[2];
    int r[4];
};

struct device_group_gate_attr
{
    char gate_name[32];
    int cam_num;
    struct device_group_cam_attr attr[4];
};

struct config_device_group
{
    int enable_group;
    int enable_group_assist;
    char ip[20]; //本机组网的相辅ip

    int gate_num;
    struct device_group_gate_attr attr[8];
};



struct config_gateway {
    int magic_number;
    struct config_worktime worktime;
    struct config_addr addr;
    struct config_reco reco;
    struct config_limit_speed limit_speed;
    struct config_radar radar;
    struct config_coil coil;
    struct config_special special;
    struct config_net net;
    struct config_face_detect face;
    struct config_vdetect vdetect;
    struct config_people_red people_red;
    struct config_gw_park park; // 停车场相关配置
    struct config_gw_car_port carpos;   // 车位相机相关配置
    struct config_http http;
    struct config_device_group device_group;
};


/****** 临时选项的配置 ******/
struct CONF_TEMP {
    char enableLiveImage;                       // 实时图像开关
    char resv[124];

    char authKey[128];                          // 机器码（字符串型）
    char authValue[256];                        // 授权码（字符串型）
    int authResult;                            // 授权认证结果(AUTH_RESULT)
};


struct RPlate {
    char plate[16];
    int plateColor;  // 0-蓝色 1-黑色 2-黄色 3-白色 4-绿色 5-红色 6-灰色 7-紫色(KISE)
    unsigned short plateX;
    unsigned short plateY;
    unsigned short plateW;
    unsigned short plateH;
    float platerealty;
};

struct reco_extra_info {
    int lane;
    int diff;
    int number; // 0 or 1
    struct RPlate plate;
    unsigned short w;
    unsigned short h;
    unsigned int len;
    char *imgdata;
};




/// LCD显示项
enum LcdDisplayItem {
  /*! 显示标题 */
  LCD_DISPLAY_ITEM_TITILE     = 0x1, 
  
  /*! 显示时间 */
  LCD_DISPLAY_ITEM_TIME       = 0x1 << 1,
  
  /*! 显示IP */
  LCD_DISPLAY_ITEM_IP         = 0x1 << 2,  
  
  /*! 显示人脸库数量 */
  LCD_DISPLAY_ITEM_PERSON_NUM = 0x1 << 3
};


enum LcdPersonDisplayItem {
  /*! 显示比对成功的人员姓名 */
  LCD_PERSON_DISPLAY_ITEM_PERSON_NAME = 0x1 << 1,
  
  /*! 显示比对成功的人员图像 */
  LCD_PERSON_DISPLAY_ITEM_PERSON_IMAGE = 0x1 << 2,
  
  /*! 显示比对成功的人员比对时间 */
  LCD_PERSON_DISPLAY_ITEM_PERSON_MATCH_TIME = 0x1 << 3,

  /*! 显示比对成功的人员自定义字段 */
  LCD_PERSON_DISPLAY_ITEM_PERSON_TEXT = 0x1 << 4
};



//------------------------------------------------------------//

/// 服务参数（8字节）。
struct ServiceParam {
  /*! 服务端口(只读 )。 */
  unsigned short port;

  /*! 最大客户端连接数，当前不生效。 */
  unsigned char max_clients;

  /*! 心跳超时时间，当前不生效。 */
  unsigned char heart_timeout;

  /*! 保留字段。 */
  unsigned char resv[4];
};

/// 分辨率。
enum PIC_SIZE_E
{
    PIC_360P = 1,  /* 640  * 360  */
    PIC_D1_PAL,    /* 720  * 576  */
    PIC_D1_NTSC,   /* 720  * 480  */
    PIC_720P       /* 1280 * 720  */
};


/// 相机容量信息。
struct MemoryInfor {
	unsigned int SDCardTotalSize; //SD卡 总容容量	单位 k
	unsigned int SDCardUsedSize;  //SD卡 已使用容量 单位 k
	unsigned int EMMCTotalSize;	  //EMMC 总容量		单位 k
	unsigned int EMMCUsedSize;    //EMMC 已使用容量 单位 k
	char resv[64]; 
};


struct ImageInfo {
  unsigned int surplus;
  unsigned int year;

  unsigned char month;
  unsigned char mday;
  unsigned char hour;
  unsigned char minute;
  
  unsigned char second;
  char wgcard[2];
  char resv[33];
};


struct SubCodParam{
  /*! 子码流 开关 0 关 !0开    默认关闭。*/
  unsigned char subcod_enable;

  /*! 子码流分辨率   enum PIC_SIZE_E*/
  unsigned char subcod_pic_size;

  /*! 保留*/
  unsigned char resv[2];

  /*! 子码流码率  单位：kbps 默认1024 恒码率时为平均码率  变码率时为最大码率 */
  unsigned int subcod_rate;

  /*! 子码流码率控制模式    0 恒码率 !0 变码率 默认0*/
  unsigned char subcod_rcMode;

  /*! 子码流输出帧率  1~30 默认 30*/
  unsigned char subcod_frame_rate;

  /*! 保留 */
  char res[16];
};




/// 相机参数(512字节)。
struct CameraParam {
  /*! 相机流名称。 */
  char stream_url[128];

  /*! 相机流端口。 */
  short stream_port;

  /*! 相机控制端口。 */
  short control_port;

  /*! 视频OSD，支持最多两行。 */
  char video_osd[2][96];

  /*! 帧率。 */
  char fps;

  /*! 饱和度。取值范围：1~255。 */
  unsigned char saturation;

  /*! 亮度。取值范围：1~100。 */
  unsigned char brightness;

  /*! 自动曝光使能开关。 */
  char enable_ae;

  /*! 最大曝光时间。单位：毫秒。取值范围：0~100。 */
  short max_exposure;

  /*! 最大增益。单位：DB。取值范围：0~40。 */
  short max_gain;

  /*! 对比度。取值范围：0~128。 */
  short contrast;

   /*! 码率。单位：kbps。 */
  unsigned short video_br;

  /*! 视频流图像宽度。 */
  unsigned short video_width;

  /*! 视频流图像高度。 */
  unsigned short video_height;

  /*! 视频流编码类型。1：H264，2：MJPEG。 */
  unsigned char video_enc_type;

  /*! 视频旋转角度 0:默认值 1：顺时针旋转90度 2：顺时针旋转180度 3：顺时针旋转270度*/
  unsigned char video_rotate;

  /*! 外接显示屏标题osd*/
  char screen_osd_title[64];
  
  /*！畸形校变使能*/
  char ldc_enable;

  char ldc_recv;

  /*! 畸变程度 -300~500*/
  int ldc_ratio;

  /*! LCD显示项开关，一个bit位对应一项开关 参见 enum LcdDisplayItem */
  unsigned int lcd_display_options;
  
    /*! 屏幕保护开关  0:关 1：开 */
  unsigned char screensaver_enable;

  /*! 宽动态开关 0:关 1：常开 2:按时间段开关 3:自动开关 */
  unsigned char wdr_enable;

  /*! 打开宽动态  时。取值范围：0~24。 */
  unsigned char wdr_open_hour;

  /*! 打开宽动态 分。取值范围：0~59。 */
  unsigned char wdr_open_minute;

   /*! 关闭宽动态 时。 */
  unsigned char wdr_close_hour;

  /*! 关闭宽动态 分。 */
  unsigned char wdr_close_minute;

  /*! 子码流 开关 0 关 !0开    默认关闭。*/
  unsigned char subcod_enable;

  /*! 子码流分辨率   enum PIC_SIZE_E*/
  unsigned char subcod_pic_size;

  /*! 子码流码率  单位：kbps 默认1024 恒码率时为平均码率  变码率时为最大码率 */
  unsigned int subcod_rate;

  /*! 子码流码率控制模式    0 恒码率 !0 变码率 默认0*/
  unsigned char subcod_rcMode;

  /*! 子码流输出帧率  1~30 默认 30*/
  unsigned char subcod_frame_rate;

  /*! lcd镜像开关 */
  char flipEnable;

  char subresv;

  /*! 比对成功人员显示项开关，一个bit位对应一项开关   参见 enum LcdPersonDisplayItem*/
  unsigned int person_display_options;
  
  /*! 定时重启开关, 0：关 !0：开 */
  unsigned char restart_enable;

  /*! 定时重启时间（小时） */
  unsigned char restart_hour;

  /*! 定时重启时间（分钟） */
  unsigned char restart_minute;
  
    /*! 视频画面输出： 0：默认值，相机自带屏幕， 1：HDMI */
  char video_output_type;

  /*! 视频画面输出大小: 0：720p60 */
  char video_output_size;

  /*! 保留。 */
  char resv2[71];
};


/// 服务（32字节）。
struct AppServicesParam {
  /*! 配置服务。 */
  struct ServiceParam config_service;

  /*! 查询服务。 */
  struct ServiceParam query_service;

  /*! 日志服务。 */
  struct ServiceParam log_service;

  /*! 保留。 */
  struct ServiceParam resv_service;
};

/// 设备描述信息参数（224字节）。
struct DescriptionParam {
  /*! 点位编号。 */
  char addr_id[32];

  /*! 点位名称。 */
  char addr_name[96];

  /*! 设备编号。 */
  char device_id[32];

  /*! 设备类型 */
  char device_type;

  /*! 保留字段。 */
  char resv[63];
};


/// 系统应用私有参数。
struct AppPrivateParam {
  /*! 各系统自行定义。 */
  char resv[512];
};

/// TCP上传参数。
struct TcpClientParam 
{
  /*! 服务器IP地址。 */
  char ip[16];

  /*! 服务器端口。 */
  int port;

  /*! 使能开关（未使用，该字段仅为兼容旧协议而加入）。 */
  char enable;

  /*! 登录验证开关。 */
  unsigned char enable_verify;

  /*! 登录验证用户名。 */
  char user_name[16];

  /*! 登录验证密码。 */
  char passwd[17];

  /*! 保留字段。 */
  char resv[65];
};


/// HTTP上传参数。
struct HttpClientParam {
  /*! 服务器IP地址。 */
  char ip[16];

  /*! 服务器端口。 */
  unsigned short port;

  /*! 服务URL。 */
  char url[102];
};

/// 4G信号信息
struct FourthGInfo
{
    int FGModuleReady; //4G模块ready
    int SIMReady;      //SIM卡ready
    int MCC;//MobileCountryCode;
    int MCN;//MobileNetworkCode; //中国移动: 0, 2, 7 中国联通:1, 6, 9  中国电信:3, 5, 11
    char dataCap[16]; //LTE etc..
    char ICCID[32];
    char IMSI[32];

    int signalStrength;  //信号强度

    int connected; //网络状态
	char resv[256];
};


/*
LCD_TYPE_WY_800_1280 = 0, // LCD_1280_800
LCD_TYPE_WY_720_1280 = 1, // LCD_1280_720
LCD_TYPE_HY070_800_1280 = 2,
LCD_TYPE_HY080_800_1280 = 3,
LCD_TYPE_CSDT050_720_1280 = 4, //Shenzhen China Star Draon Technology Co.,Ltd 华星龙
LCD_TYPE_CSDT080_800_1280 = 5, //Shenzhen China Star Draon Technology Co.,Ltd 华星龙
LCD_TYPE_PX080_800_1280 = 6,
LCD_TYPE_XHW070_1024_600 = 7,
LCD_TYPE_SQ080_800_1280 = 8,

*/

// 相机硬件信息

struct Hardware {
  /*! 芯片信息 */
  struct Chip {
    /*! 生产厂商 */
    char manu[32];

    /*! 型号 */
    char model[32];
  } chip;

  /*! 主板信息 */
  struct Board {
    /*! 生产厂商 */
    char manu[32];

    /*! 型号 */
    char model[32];
  } board;
  
  /*! 镜头信信息 */
  struct Sensor {
    /*! 生产厂商 */
    char manu[32];

    /*! 型号 */
    char model[32];    
  } sensor;

  /*! 镜头电机信息 */
  struct Motor {
    /*! 生产厂商 */
    char manu[32];

    /*! 型号 */
    char model[32]; 
    
    /*! 类型 */
    char type[16];

  } motor;
  
  /*! 显示屏信息 */
  struct Lcd {
    /*! 生产厂商 */
    char manu[32];

    /*! 型号 */
    char model[32];
	
	/* 保留 */
	char resv[4];
  } lcd;

  struct Flash {
    char manu[32];
    char model[32];
    int size;
  } flash;

  struct FourG {
    char manu[32];
    char model[32];
    int size;
  } fourg;
  
  struct WIFI {
    char manu[32];
    char model[32];
  } wifi;

  /*! 保留 */
  char resv[640];
};



/// 服器参数
struct UpdataServerParam
{
    char enable; //开关 0:关 !0:开
    char addrtype; //服务器地址类型 0:IP 1:域名/URL 
    unsigned short port;//服务器端口
    char ip[64];//服务器地址 / IP
    char URL[60]; //服务器URL
	char resv[128];  //保留
};

/// 穿透外网配置
struct ExtranetParam {
  /*! 以TCP客户端方式直达外网。 */
  union {
    struct TcpClientParam client;
	struct HttpClientParam http;
  };

  unsigned char enable;

  /*! 穿透模式，0：以TCP客户端方式直达外网。1：以 comet长轮询模式直达外网 2：以comet流模式直达外网 */
  char mode;

  /*! 保留。 */
  char resv[6];
};

/// 服务认证参数（48字节）
struct AuthParam 
{
  /*! 服务认证开关 */
  unsigned char enable;

  /*! 登录验证用户名。 */
  char user_name[16];

  /*! 登录验证密码。 */
  char passwd[17];

  /*! 保留字段。 */
  char resv[14];

  int len;  //保留

  char SdkPassword[48];   //保留
};


struct CapacityHistory
{
	/*! 最多存储的抓拍记录条数。 */
	int maxCapacity;

	/*! 已上传的抓拍记录条数。 */
	int uploadedNum;

	/*! 未上传的抓拍记录条数。 */
	int unUploadedNum;
	
	/*! 当前存储抓拍记录条数。 */
	int totalNum;

	char resv[32];
};

struct StorageCapacity
{
	/*! 最多支持添加人员名单数。 */
	int maxCapacity;

	/*! 已注册白名单条数。 */
	int whiteListNum;

	/*! 已注册黑名单条数。 */
	int blackListNum;
	
	/*! 已注册普通成员条数。 */
	int normalListNum;

	/*! 已注册成员条数。 */
	int totalNum;

	char resv[32];

};


/// 应用程序通用参数(512字节)。
struct AppCommonParam {
  struct AppServicesParam services;  //--------|-32字节--|
  struct DescriptionParam description;  //-----|-224字节-|
  struct ExtranetParam extranet;  //-----------|-128字节--|
  struct AuthParam auth;     //---------|-48字节--|
 
   /*! 保留字段。 */
  char resv[28];//-------------------------|-32字节-|

};

// 平台参数。

/// 服务(16字节)。
struct PlatformServicesParam {
  /*! 配置服务参数。 */
  struct ServiceParam config_service;

  /*! 流服务配置参数。 */
  struct ServiceParam stream_service;
};

/// 临时参数（32字节），应用程序重启后将失效。
struct TemporaryParam {
  /*! 开关视频流。 */
  char enable_video;

  /*! 各系统自行定义。 */
  char resv[27];
};


/// 平台参数(640字节)。
struct PlatformParam {
  /*! 服务。 */
  struct PlatformServicesParam services;

  /*! 相机。 */
  struct CameraParam camera;

  /*! 各平台可自行定义。 */
  char resv[112];
};


/// 流参数(64字节)。
struct StreamParam {
  /*! 视频流或JPEG流@ref ImageFormat 。 */
  int video_format;

  /*! 保留。 */
  char resv[60];
};



/// 应用程序参数(1024字节)。
struct AppParam {
  /*! 各应用程序公用参数。 */
  struct AppCommonParam common;

  /*! 私有参数。 */
  struct AppPrivateParam priv;
};

/// FTP上传参数。
struct FtpClientParam 
{
  /*! 服务器IP地址。 */
  char ip[16];

  /*! 服务器端口。 */
  int port;

  /*! 登录用户名。 */
  char user[15];

  /*! 登录密码。 */
  char password[15];

  /*! 上传目录。 */
  char pattern[70];
};



/// 连接参数。
struct ClientParam {
  /*! 模式@ref UploadMode 。 */
  char mode; /*0 未初始化。 1 TCP协议上传。 2 FTP协议上传。 3 HTTP协议上传。4 WebService上传 */

  char enable_heart; //心跳开关 目前只控制http

  /*! 保留。 */
  char resv[2];
  /*! 服务器。 */
  union {
    FtpClientParam ftp;
    TcpClientParam tcp;
    HttpClientParam http;
	HttpClientParam web_service;
  };
};


// 数据传输。

/// 上传参数。
struct UploaderParam {
  /*! 保留字段。 */
  char resv[4];

  /*! 客户端连接参数。 */
  struct ClientParam client;
};


/// 输出参数。大小应固定为128字节。
struct OutputerParam {
  struct UploaderParam uploader;
};


// 地理位置定义。
struct GeoLocation {
  /*! 经度。 */
  float longitude;

  /*! 纬度。 */
  float latitude;

  /*! 海拔高度。 */
  float altitude;

  /*! 坐标系统。1: WGS_84，2: GCJ_02。 */
  unsigned char coordinate;

  /*! 保留。 */
  char resv[3];
};




struct GB28281Param {
  /*！开关 0：关 !0：开 */
  char enable;

  /*！IPC报警级别 */
  char alarm_priority;
  
  /*！心跳周期 单位s*/
  short heart_cycle;
  
  /*！SIP服务器ID */
  char sip_server_id[32];

  /*！SIP服务器IP地址 */
  char sip_server_ip[16];

  /*！SIP服务器端口 */
  unsigned short sip_server_port;

  /*！IPC发送端口 */
  unsigned short ipc_port;

  /*！IPC ID */
  char ipc_id[32];

  /*！IPC发送密码 */
  char ipc_passwd[24];

  /*！IPC报警ID */
  char alarm_id[32];
  
  /*！IPC有效期 当前时间之后的秒数 */
  unsigned int ipc_term;

  char resv[128];
};








/// 人脸应用附加参数。
struct FaceExtraParam {
  /*! 人脸库ID。 */
  char face_set_id[32];

  /*! 地理位置。 */
  struct GeoLocation location;

  /*! 人脸库md5 */
  char face_set_md5[33];

  /*! 阿里云OSS的access_key */
  char oss_key_id[32];

  /*! 阿里云OSS的access_secret */
  char oss_key_secret[32];

  /*! 阿里云OSS数据中心位置 */
  char oss_endpoint[64];

  /*! 此设备在阿里云OSS存放位置的bucket名称  */
  char oss_bucket_name[64];

  /*! 保留。 */
  char resv1[239];

  /*gb28181参数*/	
  GB28281Param gb28181param;

  /*! 上传域名 */
  char uploader_domain[128];

  /*! 外网穿透使用域名 */
  char extra_net_domain[128];

  /*! 保留。 */
  char resv2[1004];

};










/// 子系统参数。
struct FaceSystemConfig {
  struct TemporaryParam temp;  //------28字节
  struct PlatformParam platform;  //---640字节
  struct StreamParam stream;      //---64字节
  struct AppParam app;  //-------------1024字节
  struct OutputerParam outputer;  //---128字节
  struct FaceExtraParam extraParam; //--2048 扩展参数
};

///// 坐标点定义。
//struct Point {
//  int x;
//  int y;
//};

/// 坐标点定义。
struct HA_Point {
  int x;
  int y;
};

struct SRect
{
  short x;
  short y;
  short widht;
  short height;
};


/// 语音拼接内容标记
enum SpeechSplicesFlag {
  /*! 无。*/
  SPEECH_SPLICE_FLAG_NONE = 0,

  /*! 拼接姓名。*/
  SPEECH_SPLICE_FLAG_NAME = 1,

  /*! 拼接角色定制内容 */
  SPEECH_SPLICE_FLAG_ROLE = 2,

  SPEECH_SPLICE_CUSTOMER_TEXT = 3 

};

struct FacePrivateParam {
  /*! 检测跟踪区域边数。 */
  char  roi_border_num;

  /*! 比对开关。取值为0时关闭，其它取值打开。 */
  char  enable_match;

  /*! 调试开关。 */
  char  enable_debug;
  
  /*! 深度去重复开关。1：开 0：关。 */
  char enable_dereplication;

  /*! 重复超时。超时将不再视为重复。仅在开启去重复时有效。单位：秒。取值范围：1~60。 */
  char replication_timeout;

  /*! 重复输出间隔。对于同一人员，上报人脸结果时间间隔。单位：秒。取值范围：1~120。 */
  char replication_interval;

  /*! 输出图像品质。 */
  char quality;

  /*! 名单过期自动清理功能开关。 */
  char enable_auto_clean;

  /*! 输出控制。 */
  int output_form;

  /*! 比对满分相似度值。取值范围：0.2~1.0。相似度达到该值时确信度为满分。 */
  float full_credit;

  /*! 相似度达到该值时认为比对成功（100分制）。 */
  short match_score;

  /*! 白名单GPIO输出开关（端口1）。1：开 0：关 */
  char gpio_enable_white;

  /*! 黑名单GPIO输出开关（端口2）。1：开 0：关 */
  char gpio_enable_black;

  /*! 暂未定义GPIO输出开关（端口3）。1：开 0：关 */
  char gpio_enable_resv;

  unsigned char serial_send_flag;
  unsigned char serial_databit[2];    // 数据位
  unsigned char serial_parity[2];     // 是否开始校验
  unsigned char serial_stopbit[2];    // 停止位
  int serial_baudrate[2];   // 波特率

  /*! 补光灯工作模式。1：常亮 2：自动控制 3：常闭。 */
  unsigned char light_mode;

  /*! 补光灯亮度等级(1~100)。 */
  unsigned char light_level;

  /*! 亮灯门限。画面亮度值低于该值时亮灯。亮度取值范围：1~255。 */
  unsigned char light_threshold;
  
  /*! 音量取值范围：0~100。 */
  unsigned char audio_volume;

  /*使用内置语音编号*/
  unsigned char audio_index;
  
  /*! 使用动态对比分数阈值，打开后将不使用配置的对比分数阈值。0：关 !0开*/
  char auto_score_enable;

  /*! 闸机控制类型：0继电器， 1韦根。 */
  unsigned char gateway_control_type;

  /*! 继电器序号。 */
  unsigned char alarm_index;

  /*! 继电器自动闭合持续时间，单位ms(500-5000)。 */
  unsigned short alarm_duration;

  /*! 韦根类型，WG26,WG34, WG36, WG44。目前只支持WG26, WG34。 */
  unsigned char wiegand_type;

  /*! 发行码，wg36 wg44需要此字段 */
  unsigned char wiegand_dcode;

  /*! 韦根门禁公共卡号。 */
  unsigned int wiegand_public_cardid;

  /*! 自动升成卡号时，韦根卡号范围，最小值。 */
  unsigned int wiegand_card_id_min;

  /*! 自动升成卡号时，韦根卡号范围，最大值。 */
  unsigned int wiegand_card_id_max;

  /*! 工作模式（@ref WorkMode ）。 */
  unsigned char work_mode;

  /*! 继电器状态，0表示常闭合 1表示常断开  */
  unsigned char gpio_state;

  /*! 无感录入（聚类）开关 */
  unsigned char cluster_enable;

  /*! 同一聚类通过的最大次数，当同一聚类通过的次数大于等于该次数时自动注册 */
  unsigned char max_pass_times;

  /*! 计算次数的时间间隔，在该时间间隔内只算通过一次 单位 秒*/
  unsigned int calc_times_interval;

  /*! 抓拍记录开关 0:关 !0:开*/
  char record_enable;

  /*! 断点续传开关，自动上传离线数据 */
  char record_resume_enable;

  /*人脸报警开关，打开后只要检测到人脸就报警开闸*/
  char face_alarm_enable;

 /*! 外接显示屏屏幕亮度 */
  char lcd_light_level;

  /*! gpio输入类型， 参见 enum WiegandType */
  int gpio_input_type;

  /*! gpio输入开关，0关，!0开*/
  char gpio_input_enable;

  /* 过滤未比对上的抓拍数据 0 不过滤 非0过滤  */
  char filter_not_match;

  /* 是否需要带安全帽 0 不需要 非0须要  */
  char must_wear_hat;

  /* 通行语音播放间隔 单位：秒  */
  char audio_interval;

  /* 韦根开闸时是否联动IO开闸 0:不联动 1:联动*/
  char ctrl_wiegand_io;
	
  /* 归一化保存图像开关 0:保存 !0:不保存 */
  char no_twist_image;

  /* 多人脸模式 0:单人脸检测 !0:多人脸检测 */
  char multipleFaceMod;

  /* 姓名隐私模式 0:关 !0:开         */
  char namePrivacy;

  /* 注册人员即将到期提醒时间 注: (有效时间 - alarm_expire) 至有效时间 内提醒  */
  unsigned int expire_alarm; 

  /*! 检测到人脸时打开所有继电器 。 */  
  char allGpioOut;

  /*! 抓拍记录保存位置 0：TF卡 1：相机EMMC  默认TF卡  重启生效*/
  char record_path;

  /*! 二维码识别 开关         0：关 1: 开 */
  char qr_code_enable;
  
  /*! 重复二维码    过滤间隔 0~255 S      默认 0*/
  unsigned char qr_code_interval;

  /*! 单人脸系统保留。 */  
  char resv2[16];

  /*对比模式*/
  unsigned char mache_mode;

  /*多人脸系统保留*/
  char resv_mface[19];

  /*! 检测跟踪区域坐标点。顺次连接构成检测跟踪区域。 */
  struct HA_Point roi[6];

  /*! 人脸检测最小人脸尺寸 */
  short min_face_size;

  /*! 串口配置服务开关，0：关 非0：开*/
  char serial_config_enable[2];
  
   /*! 大角度人脸过滤开关*/
  char valid_angle_enable;

  /*! 过滤人脸的最大角度，暂未使用*/
  char valid_angle;

  /*人脸质量过滤开关*/
  char valid_qvalue_enable;
  
  /*图像质量阈值*/
  char qvalue_threshold;

  /*! 人像数据同步开关 */
  char sync_enable;

  /*! 人像数据同步协议类型（暂未使用），/* 0 未初始化。 1 TCP协议。 2 FTP协议。 3 HTTP协议。4 WebService */
  char sync_mode;
  
  /*! 人像数据同步间隔时间 单位s*/
  unsigned short sync_interval;
  
  /*! 人像数据同步IP地址。 */
  char sync_ip[16];

  /*! 人像数据同步端口。 */
  unsigned short sync_port;
  
  /*! 人像数据同步URL。 */
  char sync_url[102];
  
  /*双目摄像图像差校正区域*/
  SRect bino_corret_area[3]; 

	/*! 语音拼接内容，按低字节->高字节 存拼接的内容标记 例如：char[0]=SPEECH_SPLICE_FLAG_ROLE 参见类型SpeechSplicesFlag */
  char speech_splices[4];
  
   /*! 普通人员语音播报内容（utf8编码）*/
  char normal_speech[32];
  
  /*! 白名单语音播报内容（utf8编码） */
  char white_speech[32];

  /*! 黑名单语音播报内容（utf8编码） */
  char black_speech[32];

  /*! 保存连接WIFI名称 */
  char wifi_ssid[32];
  
  char wifi_passwd[16];

  char resv[12];

  /*! 配对相机IP。 */
  char pair_ip[16];

  /*! 是否启用配对。 */
  unsigned char enable_pair;

  /*! 配对相机开闸间隔。单位：秒。 */
  unsigned char pair_timeout;

  unsigned char resv1[2];
};

struct FtpInfo{
    char user_name[15];     //用户名
    char passwd[15];        //密码
    char path[70];          //路径
    char resv[2];           //空闲
};


union Upload_Infor {
	char upload_url[102];       //抓拍数据服务URL(http上传方式时有效)
	struct FtpInfo ftp_info;    //ftp上传参数信息(ftp上传时有效);
	char tcp_resv[102];         //tcp上传方式的保留字段
	char other_resv[102];       //其它上传方式保留字段
};                   //上传方式打开时，此结构可用




struct Platform7 {
 
  unsigned sync_interval;  // 人员同步时间间隔。
  char base_url[128];    // 服务器基地址（URL）。
  char key[128]; // ACS 密钥 
  char resv[764];
};




struct Platform6 {
  unsigned sync_interval; // 人员同步时间间隔
  char base_url[128]; // 服务器基地址
  char ProjectID[128]; // 项目ID
  char Key[128]; 
  char resv[636]; // 保留
};


struct Platform5{
	char productKey[128]; 
	char productSecret[128]; 
	char deviceName[128]; //设备ID
	char deviceSecret[128]; //设备密码
	char resv[512]; //保留
};


struct Platform4{
	unsigned int synInterval; //同步时间间隔
	char serverUrl[128]; //服务器基地址
	char messagePushUrl[128]; //消息推送地址
	char userName[64]; //消息推送用户名
	char password[64]; //消息推送密码
	char itemNumber[64]; //项目编号
	char appKey[64]; //  appKey
	char appSecret[64]; //appSecret
	char resv[444]; //保留
};

struct Platform3{
	unsigned int synInterval; //同步时间间隔
	char serverUrl[128]; //服务器基地址
	char messagePushUrl[128]; //消息推送地址
	char userName[64]; //消息推送用户名
	char password[64]; //消息推送密码
	char resv[636]; //保留
};

struct Platform2{
	unsigned int synInterval; //同步时间间隔
	char serverUrl[128]; //服务器基地址
	char personSynUrl[128]; //人员同步地址
	char signUploadUrl[128]; //签到上传地址
	char personDeleteUrl[128]; //人员删除地址  请求删除人员列表
	char manageFeedBackUrl[128]; //处理反馈地址 相机操作完成后返回操作状态到此地址
	unsigned char key[8];  //数据加密秘钥
	char resv[372]; //保留
};

struct Platform1{
	unsigned int synInterval; //同步时间间隔
	char serverUrl[128]; //服务器基地址
	char personSynUrl[128]; //人员同步地址
	char signUploadUrl[128]; //签到上传地址
	char resv[636]; //保留
};

struct Platform0{
	unsigned int synInterval; //同步时间间隔
	char serverUrl[128]; //服务器基地址
	char resv[892]; //保留
};



struct PlatformAccess{
	unsigned char enable; //是否开启接入功能 0:关 1:开
	char ID [67] ; //接入方ID 000002(济工网);  
	union {
		Platform0 form0; //上传方式  000001(共用);
		Platform1 form1; //上传方式  000002(济工网); 
		Platform2 form2; //上传方式  000003(成都住建部平台); 
		Platform3 form3; //上传方式  000004(浙江工汇);
		Platform4 form4; //上传方式  000005(浙江工汇==>>成都住建部平台);
		Platform5 form5; //上传方式  000006(阿里云IOT);
		Platform6 form6; //上传方式  000007(山东聊城);
		Platform7 form7; //上传方式  000008(奥普ACS);
		char resv[1024]; //保留
	};
};

struct FaceAppParam
{
    char dev_no[32];            //设备编号
    char point_no[32];          //点位编号
    char point_name[96];        //点位名称
    char resv1[32];             //保留字段1
    unsigned char heart_beat_interval;//心跳时间间隔
    char extranet_enale;        //外网控制开关
    unsigned short extranet_port;//外网控制服务器端口
    char extranet_ip[16];       //外网控制服务器ip
    unsigned char verify_enable;//开启登录验证后，客户端在与服务器建立连接后将自动发送登录验证请求。注：抓拍机作为客户端。1：开启登录验证 0：关闭登录验证
    char user_name[15];         //登录验证用户名
    char passwd[16];            //登录验证密码
    unsigned char resv2[12];    //保留字段2
    unsigned short upload_mode; //数据上传方式0：关闭上传 1：TCP方式 2：FTP方式 3：HTTP方式
    unsigned short upload_port; //服务器端口
    char upload_ip[16];         //服务器IP
    Upload_Infor upload_info;   //上传方式打开时，此结构可用
    unsigned char cam_mode;     //相机工作模式。1：自动模式 2：在线模式 3：离线模式
    char resv3[17];             //保留字段3
    int match_enable;           //比对开关  
    int match_score;            //比对确信分数
    int dereplication_enable;   //重复过滤开关
    int dereplication_interval; //重复超时/输出间隔时间
    unsigned short output_mode; //图像输出形式  0:关闭图像输出 1：全景图 2：特写 4：比对模板 8:特征数据
	char autothresholdScore;    //自动阈值模式下，动态阈值(比对分数)
    char resv4[255];            //保留字段4
};
	

struct QueryCondition
{
    char faceID[20];        //人员ID
    char faceName[16];      //人员姓名
    unsigned int wgCardNO;  //韦根协议门禁卡号
    unsigned int timeStart; //有效期截止时间的查询起点
    unsigned int timeEnd;   //有效期截止d时间的查询终点
    unsigned int time1Start; //有效期起始时间的查询起点
    unsigned int time1End;   //有效期起始时间的查询终点
	unsigned long long  wgCardNOLong; //韦根协议门禁卡号  wgCardNO长度不满足时使用此项
    unsigned char resv[248];
};

/// 抓拍记录查询条件
struct RecordCondition {
  // 抓拍图像数据标记 0：不需要，非0：需要。
  char img_flag;

  // 注册图像数据标记 0：不需要，非0：需要。
  char reg_img_flag;

  // 保留 以0填充
  char resv1[2];

  // 匹配模式，0精确匹配，非0模糊匹配
  unsigned short query_mode;

  // 条件组合标记
  unsigned short condition_flag;    //RecordQueryFlag

  // 抓拍时间区间起点
  unsigned int time_start;

  // 抓拍时间区间终点
  unsigned int time_end;

  // 比对分数区间起点
  short score_start;

  // 比对分数区间终点
  short score_end;

  // 性别
  unsigned char sex;

  // 年龄区间起点
  unsigned char age_start;

  // 年龄区间终点
  unsigned char age_end;

  // 保留 以0填充
  char resv2[17];
  
  // 比对上的人员ID
  char person_id[20]; 
  
  // 比对上的人员姓名
  char person_name[16];
  
  // 人像质量区间起点
  unsigned char qvalue_start;

  // 人像质量区间终点
  unsigned char qvalue_end;

  // 是否已经上传 1:表示已经上传 0：表示未上传
  char upload_state;

  char resv4;

  // 序列号
  unsigned int suquce;

  // 保留 以0填充
  char resv3[60];
};

struct SnapshotImage
{
    // 快照时间戳 秒
    unsigned int  timeStamp_s;

    // 快照时间戳 毫秒
    unsigned int  timeStamp_u;

    // 快照图像长度
    int snapImageSize;

    // 快照图像
    unsigned char *snapImage;
};

//开闸纪录，相机开闸后上报的开闸纪录
struct AlarmInfoRecord  
{
    char cameraID[32];      //相机编号
    char alarmTime[20];     //开闸时间     格式：2018/3/6    16:38:20
    unsigned char alarmDeviceType;//开闸设备类型，0：继电器 1：韦根设备
    char resv[3];           //保留
    char personID[20];     //人员id，报警开闸的人员id
    unsigned int alarmDeviceId;//开闸设备id，外设类型为继电器时，外设ID为GPIO端口号。外设类型为支持韦根协议的设备时，外设ID为卡号。
	unsigned long long  wgCardNOLong;   // 韦根门禁卡号加长 在alarmDeviceId长度不满足时使用此成员
};



//开闸请求，当相机处于在线模式时，需要开闸时会向平台发送该请求
struct AlarmRequest
{
	char cameraID[32];      //相机编号
	char personID[20];     //人员id，需要开闸的人员id
	char requestTime[20];   //请求时间     格式：2018/3/6    16:38:20 
	unsigned char alarmDeviceType;//请求的开闸设备类型，0：继电器 1：韦根设备
	unsigned char alarmDeviceState;//当前开闸设备状态，0：未启用 1：启用
	char resv[2];           //保留
	unsigned int alarmDeviceId;//开闸设备id，外设类型为继电器时，外设ID为GPIO端口号。外设类型为支持韦根协议的设备时，外设ID为卡号。
	unsigned long long  wgCardNOLong;   // 韦根门禁卡号加长 在alarmDeviceId长度不满足时使用此成员
	int type; // 请求开闸类型 0 普通请求 1:用户密码验证开闸 2: 二维码开闸
	union{

		struct {
			char userName[64];
			char password[64];
		}userVerify; //用户密码验证开闸;

		struct {
			char qrCode[1024];
		}qrcodeVerify; //用户密码验证开闸;

		char recv[1024];
	};
};


enum ComponentType
{
	HA_COMPONENT_TYPE_NONE = 0,               //未定义
	HA_COMPONENT_TYPE_BACKGROUND_IMAGE,		//背景图片      图像 包含图像数据
	HA_COMPONENT_TYPE_IP,						//IP显示		文字
	HA_COMPONENT_TYPE_REGISTER_NUM,			//注册人数		文字
	HA_COMPONENT_TYPE_TIME,					//时间显示		文字
	HA_COMPONENT_TYPE_TITLE,					//标题显示位置	文字
	HA_COMPONENT_TYPE_NEWS,					//资讯显示		文字
	HA_COMPONENT_TYPE_MATCH,					//比对框显示    图像 包含图像数据
	HA_COMPONENT_TYPE_MATCH_FACE,			//比对框中人脸显示  文字 相对比对框位置
	HA_COMPONENT_TYPE_MATCH_ID,			//比对框中ID显示	文字
	HA_COMPONENT_TYPE_MATCH_NAME,			//比对框姓名显示	文字
	HA_COMPONENT_TYPE_MATCH_DATE			//比对框日期显示	文字
};


struct UIComponentParam
{
	int component_type;   //  enum ComponentType
	int x, y;  //坐标 左上为坐标原点 水平 x 垂直 y
	unsigned int font_size;
	unsigned int  font_color; //文字属性
	unsigned int data_size; // 图像长度
	char resv[32]; //保留
	char *data; //图像数据
};








#endif /* CONFIG_GW_H_ */
