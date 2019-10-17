#ifndef FACE_RECO_DEF_H
#define FACE_RECO_DEF_H

#include "config_gw.h"







/// 单天最大调度时段数。
#define MAX_SCHEDULE_PER_DAY 6

/// 调度最大分类数。分类自行定义，范围：1~5。
#define MAX_SCHEDULE_KIND 5

/// 单周天数。
#define ONE_WEEK_DAYS     7

/// 调度模式。
enum ScheduleMode {
	/*! 禁用。 */
	SCHEDULE_MODE_NONE = 0,

	/*! 按天调度。 周1-周7 都按照此设置运行  */
	SCHEDULE_MODE_DAILY = 1,   

	/*! 按周调度。 周1-周7分别设置*/
	SCHEDULE_MODE_WEEKLY = 2
};

/// 时间点。
struct MinuteSchedule {
	/*! 时。取值范围：0~24。 */
	unsigned char hour;

	/*! 分。取值范围：0~59。 */
	unsigned char minute;
};

/// 时间段。
struct HourSchedule {
	/*! 起始时间。闭区间（包含该值）。 */
	MinuteSchedule start;

	/*! 结束时间。开区间（不包含该值）。 */
	MinuteSchedule end;
};


/// 按天调度。
struct DailySchedule {
	unsigned int Sector; // 一天内时间总段数 最大支持6段   设置Schedule[0]--Schedule[1].......Schedule[Sector] 内为开闸时间
	HourSchedule SchTime[6];  // 调度时间 在此时间段为开闸时间
	char recv[16]; //保留 
};

/// 分类调度。
struct KindSchedule {
	enum ScheduleMode Mode; //调度模式 
	char ScheduleName[16];  //类别名称  自定义
	unsigned short ScheduleNameCode; //类别代码  取值 [1~5] 不能重复   
	/*调度模式为 SCHEDULE_MODE_DAILY 时 只读取Schedule[0] 配置  
	为 SCHEDULE_MODE_WEEKLY 时周日 到 周六 按Schedule[0]-Schedule[5] 配置 */
	DailySchedule Schedule[7];  //调度时间 
	char recv[32]; //保留 
};






enum HatDetectResult
{
	/*! 未检测到安全帽 */
    NO_HAT = 0, 
    /*! 蓝色安全帽 */
    HAVE_BLUE_HAT,
    /*! 橙色安全帽 */
    HAVE_ORANGE_HAT,  
    /*! 红色安全帽 */
    HAVE_RED_HAT,
    /*! 白色安全帽 */
    HAVE_WHITE_HAT,
    /*! 黄色安全帽 */
    HAVE_YELLOW_HAT
};

// 人员比对成功类型

enum MatchType {
  /*! 未知 */
  MATCH_TYPE_NULL                  = 0x0,

  /*! 刷脸比对成功 */

  MATCH_TYPE_NORMAL                = 0x1,

  /*! 人证比对成功 */

  MATCH_TYPE_IDCARD_1TO1           = 0x1 << 1,

  /*! 刷身份证比对 */

  MATCH_TYPE_IDCARD                = 0x1 << 2,

  /*! 刷卡比对成功 */

  MATCH_TYPE_WGCARD                = 0x1 << 3,

  /*! 过人开闸 */

  MATCH_TYPE_ANY_FACE              = 0x1 << 4
};


struct FaceRecoInfo
{
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
	char userParam[68]; //用户自定义信息
};

//相机系统时间信息
struct SystemTime
{
    char time_zone;         //时区
    char date[11];          //日期 2017/12/6（2017年12月6日）
    char time[9];           //时间   17:37:05
    char resv[11];          //保留
};


struct ha_rect{
  short x;
  short y;
  short width;
  short height;
};



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

struct FaceFeature 
{
	float *feature; //特征数据
	short featureseize; //单个特征长度
	short featureNum; //特征数量
};
struct FaceImage
{
    int img_seq;    //图片编号
    int img_fmt;    //图片格式 0：jpg 1：bgr 
    unsigned char *img; //要注册的人脸图片数据，支持主流图像格式
    int img_len;    //img的长度
    int width;      //图像宽度，jpg图像不填此项
    int height;     //图像高度，jpg图像不填此项
};

struct ErrorFaceImage
{
    int img_seq;    //注册失败的图像编号
    int err_code;   //失败的错误码
};

//人脸查询返回
struct QueryFaceFlags 
{
    char personID[20];           //人员ID
    char personName[16];         //姓名 
	short feature_count;         //当前id的特征数总量
    int featureSize;             //人脸特征数据大小
    float feature[2048]; //人脸特征数据
    int imgNum;                  //图像数目
    int imgSize;                 //图像大小
	unsigned char img[10240];    //图像数据
    int role;           //人员角色，0：普通人员。 1：白名单人员。 2：黑名单人员。 -1：所有人员。
    unsigned int wgCardNO;//韦根协议门禁卡号
    unsigned int effectTime;   //有效期截止时间，该人员信息在该时间内有效,从1970年1月1日0时0分0秒到截止时间的秒数（0xFFFFFFFF表示永久有效，0表示永久失效）
    unsigned int effectStartTime;//有效期起始时间，该人员信息在该时间之后有效,从1970年1月1日0时0分0秒到起始时间的秒数（0表示未初始化）	
};

//人脸查询回调返回
struct QueryFaceInfo
{
    int record_count;            //查询的角色记录总量
    int record_no;               //当前收到的记录序号
    char personID[20];           //人员ID
    char personName[16];         //姓名   
    int role;                    //人员角色 0：普通人员。 1：白名单人员。 2：黑名单人员。 -1：所有人员。
    short feature_count;         //当前id的特征数总量
    short feature_size;           //人脸特征数据长度
    float *feature;              //人脸特征数据，按顺序排列所有特征数据 featureSize*feature_count
    int imgNum;                     //模板图像数量
    int imgSize[5];                 //图像大小，imgSize[i]为第i张图片的大小
    char imgFmt[5][4];              //图像格式,imgFmt[i]为第i张图片的格式
    unsigned char *imgBuff[5];          //imgBuff[i]位第i张图片给数据首地址
    unsigned int wgCardNO;                       //韦根门禁卡号
    unsigned int  effectTime;   //有效期截止时间，该人员信息在该时间内有效,从1970年1月1日0时0分0秒到截止时间的秒数（0xFFFFFFFF表示永久有效，0表示永久失效）  
    unsigned int  effectStartTime;   //有效期起始时间，该人员信息在该时间之后有效,从1970年1月1日0时0分0秒到起始时间的秒数（0表示未初始化）
	short version;                 //非0:当前特征数据版本 0:不支持版本查询
	unsigned char ScheduleMode;  //调度模式 0:不使用调度模式  1~5 对应 Struct KindSchedule->ScheduleNameCode模式
 	char resv;
	int twistImgNum;//归一化图像数量
	short twistwidth[5];					//归一化图像宽度
    short twistheight[5];					//归一化图像高度
	int twischannel[5];                   //归一化图像通道
	char *twistimgBuff[5];          //归一化图像第i张图片给数据首地址
	unsigned long long wgCardNOLong;   // 韦根门禁卡号加长 在wgCardNO长度不满足时使用此成员
	char userParam[68];  //用户自定义文本内容，可用于相机TTS播放、LCD显示，也可作为用户平台自定义属性使用
	char resv1[436];
};

/// 抓拍比对纪录。
struct RecordData {
  /*! 查询的角色记录总量 */
  int record_count;            

  /*! 当前收到的记录序号 */
  int record_no;

  /*! 抓拍纪录序列号 */
  unsigned int sequence;

  /*! 抓拍时间秒数，从1970年01月01日00时00分00秒至抓拍时间经过的秒数。 */
  unsigned int tvSec;

  /*! 抓拍时间微秒数，tvSec的尾数 */
  unsigned int tvUsec;

  /*! 比对状态(分数) */
  short matched;

  /*! 性别 */
  unsigned char sex;
  
  /*! 年龄*/
  unsigned char age;

  /*! 比对上的人员id */
  char person_id[20];

  /*! 比对上的人员姓名 */
  char person_name[16];

  /*！实时人脸图像长度 */
  int face_image_len;

  /*！实时人脸图像（jpg格式） */
  unsigned char* face_image;

  /*! 人脸位于特写图像的X坐标。 */
  unsigned short faceXInFaceImg;

  /*! 人脸位于特写图像的y坐标。 */
  unsigned short faceYInFaceImg;

  /*! 人脸位于特写图像的宽度 */
  unsigned short faceWInFaceImg;

  /*! 人脸位于特写图像的高度 */
  unsigned short faceHInFaceImg;

  /*！比对上的注册人脸图像长度，未比对上时为0*/
  int reg_image_len;

  /*！比对上的注册人脸图像（jpg格式），未比对上时为NULL */
  unsigned char* reg_image;

  /*! 人像质量。 */
  unsigned char qvalue;

  /*! 纪录是否已上传 1:表示已经上传 0：表示未上传*/
  char is_upload;
  /* ! 人员角色 仅当matched>0有效  人员角色，0：普通人员。 1：白名单人员。 2：黑名单人员 -2：无此信息 */
  char role;
  /*! 保留 */

  char resv;

  unsigned int match_type; // 比对类型 参见MatchType
};

//NTP校时信息
struct NtpInfo
{
    short enable_state;         //Ntp开关状态，0是关 非0是开
    short update_cycle;         //更新周期，60~600s
    char ntp_server[16];        //NTP服务器ip地址
	char resv[12];              //保留
};

//NTP校时信息
struct NtpInfoEx
{
    short enable_state;         //Ntp开关状态，0是关 非0是开
    short update_cycle;         //更新周期，60~600s
    char ntp_server[16];        //NTP服务器ip地址
    char domain[64];            //NTP服务器域名  IP为空时使用   
	char resv[128];              //保留
};



//系统网络信息
struct SystemNetInfo
{
    char mac_addr[18];      //网卡物理地址
    char ip_addr[16];       //相机ip地址
    char netmask[16];       //子网掩码
    char gateway[16];       //默认网关
    char resv[14];          //保留
};

struct SystemNetInfoEx
{
	char mac[20];          // 网卡MAC地址
	char ip[20];           // 网卡IP地址
	char netmask[20];      // 网上子网掩码
	char gateway[20];      // 网关

	char manufacturer[16]; // 制造商名称
	char platform[32];     // 平台名称
	char system[32];       // 系统名称
	char version[64];      // 版本
	char ip_2[16];         // 网卡2IP地址
    char netmask_2[16];    // 网卡2子网掩码
    char dns[16];		       // 域名服务器地址
    char dhcp_enable;	     // DHCP开关
    char resv[64];		     // 保留
};

//系统版本信息
struct SystemVersionInfo
{
    char dev_id[32];        //设备序列号
    char protocol_ver[8];   //协议版本
    char firmware_ver[16];  //固件版本
    char code_ver[8];       //应用程序版本
    char build_time[20];    //应用编译时间
    char resv[16];          //保留
    char systemp_type[16];  //系统类型   
    char plateform[16];     //硬件平台
    char sensor_type[16];   //传感器型号
    char algorithm_ver[16]; //算法版本
    char min_sdk_ver[16];   //最低sdk版本
    unsigned int min_client_ver;//最低客户端版本
	char kernel_version[128];  //内核版本
	char lcd_type[32]; //LCD屏型号
	char recv[512]; //保留
};




struct FaceRect
{
    unsigned int faceId;        //人脸轮廓id
    struct ha_rect faceRect;//人脸轮廓坐标
    char resv[4];
};

struct FaceRectInfo
{
    char idShowFlag; //显示轮廓开关
    char resv[3];
    int rectNum;       //轮廓数量
    struct FaceRect faceRects[32];
};

struct FaceDelProgressInfo
{
    int delCount;   //删除的纪录总数
    int curDelNo;   //当前删除第几条纪录
    char faceId[20];//当前删除的人员ID
};

struct FaceReRegistProgressInfo
{
    int regist_count;     //重注册的人员总数
    int cur_regist_no;    //当前重注册第几条纪录
    char faceId[20];      //当前重注册的人员id
};


struct DebugImage
{
    int format;     //调试图像格式,0 rgb 1:jpg
    short width;        //调试图像宽度
    short height;       //调试图像高度
    int imageLen;       //图像数据长度
    unsigned char *imgData;//图像数据
};

struct BebugInfraredImage
{
	int lived;          // 0非活体 1 活体
	unsigned int timeStamp_s;     //时间戳 秒
    unsigned int timeStamp_u;     //时间戳 微妙
	short x_deviations;  //图像x坐标相差值
	short y_deviations;	//图像y坐标相差值
	ha_rect normalImgeRect;  //可见光图像人脸矩形
	ha_rect infraredImgeRect;	//红外光图像人脸矩形
	unsigned int viewImgeNum; //全景图数量
	DebugImage viewImge[8];  //全景图数据
	unsigned int closeupImgeNum;  //特写图数量
	DebugImage  closeupImge[8]; //特写图数据
	
};


struct BinocularAjustParam{
	unsigned int coordinatesNum; //x,y相差坐标数量 1,2字段循环
	short* x_deviations;  //图像x坐标相差值
	short* y_deviations;	//图像y坐标相差值
	unsigned int imgeNum; //用于校正的图像数量
	unsigned int* imgeFormat; //图像格式
	unsigned short* imgeWidth;  //图像宽度
	unsigned short* imgeHeight;  //图像高度
	unsigned int * imgeLen;   //图像长度
	char** imge;   //图像数据
};





struct BinocularAjustReply{
	short status;  //校准状态 是否已经计算双目像差 0：未计算 ！0已计算
	short coordinatesNum; //相差个数  3,4字段循环；
	short x_deviations[16];   //x坐标相差值 最多16个
	short y_deviations[16];  //y坐标相差值	最多16个
};
struct AllPersonID{
	int count; //注册人员数
	char** Id;  //Id[num]为一个成员id字符串的首地址
};
struct DebugImageInfo
{
    unsigned int timeStamp_s;     //时间戳 秒
    unsigned int timeStamp_u;     //时间戳 微妙
    int matched;                //比对结果，0：未比对。-1：比对失败。1：比对成功
    int matchScore;            //比对分数
    char faceId[20];            //比对上的人员id，matched等于1时有效
    int imageNum;               //调试图像数量，最大支持6张图像
    struct DebugImage debugImage[6];       //调试图像信息
};

#endif

