#ifndef HA_SDK_H
#define HA_SDK_H

#include <stdio.h>


#include "HASdkDef.h"






struct HA_Cam;
struct HA_LiveStream;
struct CamCtrl;
struct CamCtrlAutoCtrl;
struct CamCtrlMannualCtrl;
struct CamCtrlLED;
struct CamCtrlImageEnhance;
struct CamCtrlExtSync;
struct FaceFlags;
struct LocalNetInfo;


#ifdef __cplusplus
extern "C" {
#endif


/*
 * @brief   取得sdk版本
 * @param   version[out] sdk版本信息  
 * @return  版本号    【返回值固定3】
 */
HASDK_API int HASDK_CALL HA_GetVersion(struct HaSdkVersion *version);


/*
 * @brief   将sdk版本转换成int类型
 * @param   sdkVersion[in] sdk版本信息  
 * @return  版本号
 */
HASDK_API int HASDK_CALL HA_VersionToInt(char *version);

/*
 * @brief   版本检查
 * @param   sdkVersion[in] sdk版本信息
 * @param   systemVersion[in] 相机版本信息
 * @return  匹配返回0 其他参数错误码
 */
HASDK_API int HASDK_CALL HA_VersionCheck(struct HaSdkVersion *sdkVersion, struct SystemVersionInfo *systemVersion);

/**
 * @brief   sdk初始化
 * @brief   2)与HA_InitEx这两个函数，二者只能调其中一个。
 * @brief   3)如果想连接更多相机，请调用HA_InitEx
 * @param   无
 * @return  无
 */
HASDK_API void HASDK_CALL HA_Init();

/**
* @brief   sdk初始化
* @param   maxCamNum[in] 废弃 任意数字
* @return  无
*/
HASDK_API void HASDK_CALL HA_InitEx(unsigned int maxCamNum);

/**
* @brief   人脸提取器初始化，多个相机时也只需要初始化一次
* @param   faceModel 填NULL。
* @return  无
*/
HASDK_API int HASDK_CALL HA_InitFaceModel(const char *faceModel);

/**
* 预留
*/
HASDK_API int HASDK_CALL HA_SetFastFace(int mode);

/**
* @brief   设置注册人脸合法性检查 默认为开
* @param   onoff !0为开   0为关  
* @return  无
*/
HASDK_API int HASDK_CALL HA_SetFaceCheckEnable(int onoff);

/**
 * @brief   设置SDK日志开关 注:默认为打开
 * @param   enable[in]   0:关  !0:开
 * @return  无              
 */
HASDK_API void HASDK_CALL HA_LogEnable(char enable);

/**
 * @brief   sdk反初始化
 * @param   无
 * @return  无
 */
HASDK_API void HASDK_CALL HA_DeInit();

/**
 * @brief   注册连接事件回调函数,须先调用HA_SetNotifyConnected(1)才生效
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegConnectEventCb(HA_ConnectEventCb_t cb, int usrParam);

/**
 * @brief   注册连接事件回调函数,须先调用HA_SetNotifyConnected(1)才生效
 * @param   cam[in] 产生回调的相机句柄
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegConnectEventCbEx(HA_Cam* cam, HA_ConnectEventCb_t cb, int usrParam);

/**
 * @brief   注册认证状态回调，对重连时有效，第一次连接不可用
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegVerifyStatusCbEx(HA_Cam* cam, HA_VerifyStatusCb_t cb, void* usrParam);

/**
 * @brief   注册全局实时流回调函数 (未解码)
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegLiveStreamCb(HA_LiveStreamCb_t cb, int usrParam);

/**
 * @brief   注册实时流回调函数 (未解码)
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegLiveStreamCbEx(HA_Cam* cam, HA_LiveStreamCb_t cb, int usrParam);

/**
 *废弃
 */
HASDK_API void HASDK_CALL HA_RegDataReadCb(HA_DataReadCb_t cb, int usrParam);


/**
 * 废弃
 */
HASDK_API void HASDK_CALL HA_RegDataReadCbEx(HA_Cam* cam, HA_DataReadCb_t cb, int usrParam);

/**
 * @brief   注册获取双目相机校差参数回调函数
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegBinocularAjustParam(HA_Cam* cam,HA_BinocularAjustParamCb_t cb, void* usrParam);

/**
 * @brief   注册人脸抓拍数据接收回调函数
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegFaceRecoCb(HA_Cam* cam, HA_FaceRecoCb_t cb, void* usrParam);

/**
 * @brief   注册人脸查询数据回调函数
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegFaceQueryCb(HA_Cam* cam, HA_FaceQueryCb_t cb, void* usrParam);

/**
 * @brief   注册人脸抓拍纪录数据回调函数
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegFaceRecordQueryCb(HA_Cam* cam, HA_FaceRecordCb_t cb, void* usrParam);

/**
 * @brief   注册人脸轮廓信息回调函数
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegFaceRectCb(HA_Cam* cam, HA_FaceRectCb_t cb, void* usrParam);

/**
 * @brief   注册红外调试图像回调函数
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegFaceDebugInfraredImageCb(HA_Cam* cam, HA_FaceDebugInfraredImageCb_t cb, void* usrParam);

/**
 * @brief   注册调试图像回调函数
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegFaceDebugImageCb(HA_Cam* cam, HA_FaceDebugImageCb_t cb, void* usrParam);

/**
 * @brief   注册人脸删除进度回调函数
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegFaceDeleteProgressCb(HA_Cam* cam, HA_FaceDelProgressCb_t cb, void* usrParam);

/**
 * @brief   注册人脸重注册进度回调函数
 * @param   cb[in] 回调函数指针
 * @param   usrParam[in] 用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_RegFaceReRegistProgressCb(HA_Cam* cam, HA_FaceReRegistProgressCb_t cb, void* usrParam);

/**
* @brief   注册搜索相机回调函数
* @param   cb[in] 回调函数指针
* @param   usrParam[in] 用户参数
* @return  无
*/
HASDK_API void HASDK_CALL HA_RegDiscoverIpscanCb(discover_ipscan_cb_t cb, int usrParam);

/**
* 废弃                       
*/
HASDK_API void HASDK_CALL HA_RegOfflineDataCb(HA_Cam* cam,HA_OfflineFeeData_t cb, int usrParam);


/**
* 废弃                      
*/ 
HASDK_API void HASDK_CALL HA_RegQueryEntryPlateInfoCb(HA_Cam* cam,HA_OfflineQueriedEntryInfoCb_t cb, int usrParam);

/**
* @brief   注册回调函数,功能是获取系统快照
* @param   cb[in] 回调函数指针
* @param   usrParam[in] 用户参数
* @return  无                       
*/ 
HASDK_API void HASDK_CALL HA_RegSnapshotCb(HA_Cam* cam, HA_SnapshotCb_t cb, void* usrParam);

/**
* @brief   注册回调函数,功能是接收开闸纪录
* @param   cb[in] 回调函数指针
* @param   usrParam[in] 用户参数
* @return  无                       
*/ 
HASDK_API void HASDK_CALL HA_RegAlarmRecordCb(HA_Cam* cam, HA_AlarmRecordCb_t cb, void* usrParam);

/**
* @brief   注册回调函数,功能是接收开闸请求
* @param   cb[in] 回调函数指针
* @param   usrParam[in] 用户参数
* @return  无                       
*/ 
HASDK_API void HASDK_CALL HA_RegAlarmRequestCb(HA_Cam* cam, HA_AlarmRequestCb_t cb, void* usrParam);

/**
* @brief   注册回调函数,功能是接收相机执行Ping命令结果
* @param   cb[in] 回调函数指针
* @param   usrParam[in] 用户参数
* @return  无                       
*/ 
HASDK_API void HASDK_CALL HA_RegCamPingCb(HA_Cam* cam, HA_CamPingCb_t cb, void* usrParam);

/**
* @brief   注册回调函数,功能是接收相机搜索WiFi列表
* @param   cb[in] 回调函数指针
* @param   usrParam[in] 用户参数
* @return  无                       
*/ 
HASDK_API void HASDK_CALL HA_RegSearchWiFiCb(HA_Cam* cam, HA_SearchWiFiCb_t cb, void* usrParam);


/**
* @brief   注册回调函数,功能是接收相机连接wifi状态 
* @param   cb[in] 回调函数指针
* @param   usrParam[in] 用户参数
* @return  无                       
*/ 
HASDK_API void HASDK_CALL HA_RegWifiConnectCb(HA_Cam* cam, HA_WifiConnectCb_t cb, void* usrParam);


/**
* @brief   注册回调函数,功能是接收相机扫描二维码数据 
* @param   cb[in] 回调函数指针
* @param   usrParam[in] 用户参数
* @return  无                       
*/ 
HASDK_API void HASDK_CALL HA_RegQRCodeCb(HA_Cam* cam, HA_QRCodeCb_t cb, void* usrParam);


/**
* 废弃
*/
HASDK_API void HASDK_CALL HA_QueryOfflineEntryTimeByPlate(struct HA_Cam* cam,const char* plate);

/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_QueryOfflineFeeDataCountAndMoney(struct HA_Cam* cam, const char *pStartTime, const char *pEndTime,int queryStyle,void*pPlateOrVehicleType,int *pCount,float* pMoneyTotal);


/**
*  废弃
*/
HASDK_API int HASDK_CALL HA_QueryOfflineFeeDataByPage(struct HA_Cam* cam, const char *pStartTime, const char *pEndTime,int queryStyle,void*pPlateOrVehicleType,int startPos,int endPos);


/**
*  废弃
*/
HASDK_API int HASDK_CALL HA_ClearOfflneFeeData(struct HA_Cam* cam);


/**
* 废弃
*/
HASDK_API void HASDK_CALL HA_RegQueryOfflineFeeDataByPageCb(HA_Cam* cam,HA_OfflineFeeDataQueriedByPageCb_t cb, int usrParam);


/**
* @brief   搜索相机
* @param   无
* @return  无
*/
HASDK_API void HASDK_CALL HA_DiscoverIpscan();

/**
* @brief   通过mac地址，跨网段设置相机IP
* @param   mac[in] mac地址
* @param   ip[in] 相机IP
* @param   netmask[in] 子网掩码
* @param   gateway[in] 默认网关
* @return  无                    
*/
HASDK_API void HASDK_CALL HA_SetIpBymac(const char* mac, const char* ip, const char* netmask, const char* gateway);

/**
 * 废弃                                  
 */
HASDK_API void HASDK_CALL HA_SetCamType(enum CAM_TYPE camType);

/**
 * @brief   SDK编码类型
 * @param   charEncode   编码方式 默认CHAR_ENCODE_UTF8
 * @return  0 未连接
 * @return  1 已连接
 */
HASDK_API void HASDK_CALL HA_SetCharEncode(CHAR_ENCODE charEncode);

/**
 * @brief   是否连接相机
 * @param   cam[in]   相机句柄
 * @return  0 未连接
 * @return  1 已连接
 */
HASDK_API int HASDK_CALL HA_Connected(struct HA_Cam* cam);

/**
 * @brief   连接相机。请用HA_ConnectEx替代   
 * @param   ip[in]   相机ip
 * @param   port[in]   相机端口，固定为9527
 * @param   usrName[in]   用户名，传空为初始默认 admin
 * @param   password[in]   密码，传空为初始默认 admin
 * @param   errorNum[out]  连接失败错误号，0为连接成功，-1为连接失败
 * @return  NULL 连接失败
 * @return  非NULL 连接成功         
 */
HASDK_API struct HA_Cam* HASDK_CALL HA_Connect(const char* ip, unsigned short port, const char* usrName, const char* password, int* errorNum);

/**
* @brief   连接相机
* @param   ip[in]   相机ip
* @param   port[in]   相机端口，固定为9527
* @param   usrName[in]   用户名，传空为初始默认 admin
* @param   password[in]   密码，传空为初始默认 admin
* @param   errorNum[out]  连接失败错误号，0为连接成功，-1为连接失败
* @param   channel[in]  码流通道号，有特殊需求的用户使用，无特殊需求用户直接传0通道即可
* @param   autoReconn[in] 自动重连标志，为1自动重连，0不会自动重连
* @return  autoReconn为1时，固定返回相机句柄
* @return  autoReconn为0时，连接成功时返回相机句柄，连接失败时返回NULL
* @return  建议用户使用自动重连,autoReconn为1
*/
HASDK_API struct HA_Cam* HASDK_CALL HA_ConnectEx(const char* ip, unsigned short port, const char* usrName, const char* password, int* errorNum, unsigned int channel, int autoReconn);

/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_ModifyUserNamePasswd(HA_Cam* cam,const char* usrNameOld, const char* passwordOld,const char* usrNameNew, const char* passwordNew);

/**
* @brief   用户认证请求,用户名和密码使用cam->usrName、cam->passwd
* @param   cam[in]   相机句柄
* @param   port[in]  认证的端口 HASX_CONFIG_PORT 或者 HASX_CAM_PORT
* @return  0 获取成功
* @return  <0 获取失败
*/
HASDK_API int HASDK_CALL HA_VerifyCam(struct HA_Cam *cam, int port);

/**
 * @brief   断开相机
 * @param   cam[in]   相机句柄
 * @return  无
 */
HASDK_API void HASDK_CALL HA_DisConnect(struct HA_Cam* cam);

/**
 * @brief   设置视频流格式
 * @param   cam[in]   相机句柄
 * @param   视频流格式[in]    ) 0:BGR24 !0:RGB24
 * @return  无
 */
HASDK_API void HASDK_CALL HA_SetStreamFmt(struct HA_Cam* cam, int decodeFmt);

/**
 * 废弃
 */
HASDK_API void HASDK_CALL HA_StartStream(struct HA_Cam* cam, HWND hWnd);

/**
 * 废弃
 */
HASDK_API void HASDK_CALL HA_StartStreamEx(struct HA_Cam* cam, HWND hWnd, HA_DecodeImageCb_t cb, int usrParam);

/**
 * 废弃
 * @return  无
 */
HASDK_API void HASDK_CALL HA_StartStream1(struct HA_Cam* cam, HWND hWnd);

/**
 * 废弃
 * @return  无
 */
HASDK_API void HASDK_CALL HA_StartStreamEx1(struct HA_Cam* cam, HWND hWnd, HA_DecodeImageCb_t cb, int usrParam);


/**
 * @brief   开始显示视频流
 * @param   cam[in]    相机句柄
 * @param   hWnd[in]   窗口句柄 可为NULL
 * @param   cb[in]     解码图像回调 可为NULL，注此回调不能阻塞，否则影响实时画面流畅度
 * @param   usrParam[in]   解码图像回调用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_StartStreamRv(struct HA_Cam* cam, HWND hWnd, HA_DecodeImageExCb_t cb, void* usrParam);

/**
 * @brief   开始显示红外视频流
 * @param   cam[in]    相机句柄
 * @param   hWnd[in]   窗口句柄 可为NULL
 * @param   cb[in]     解码图像回调 可为NULL，注此回调不能阻塞，否则影响实时画面流畅度
 * @param   usrParam[in]   解码图像回调用户参数
 * @return  无
 */
HASDK_API void HASDK_CALL HA_StartStreamRv1(struct HA_Cam* cam, HWND hWnd, HA_DecodeImageExCb_t cb, void* usrParam);


/**
 * @brief   绘制人脸轮廓
 * @param   cam[in]    相机句柄
 * @param   rect[in]   人脸框区域1080p
 * @param   rect_num[in] 人脸框数量
 * @return  无
 */
HASDK_API void HASDK_CALL HA_DrawFaceRects(struct HA_Cam *cam, struct ha_rect *rect, int rect_num);

/**
 * @brief   设置需要显示的矩形框
 * @param   cam[in]    相机句柄
 * @param   rect[in]   矩形框区域1080p
 * @return  无
 */
HASDK_API void HASDK_CALL HA_SetDrawRect(struct HA_Cam *cam, struct ha_rect *rect);

/**
 * @brief   开始绘制矩形框
 * @param   cam[in]    相机句柄
 * @return  无
 */
HASDK_API void HASDK_CALL HA_StartDrawRect(struct HA_Cam *cam);

/**
 * @brief   停止绘制矩形框
 * @param   cam[in]    相机句柄
 * @return  无
 */
HASDK_API void HASDK_CALL HA_StopDrawRect(struct HA_Cam *cam);



/**
 * @brief   终止显示某一个窗口句柄视频流
 * @param   cam[in]   相机句柄
 * @return  无
 */
HASDK_API void HASDK_CALL HA_StopStreamEx(struct HA_Cam* cam, HWND hWnd);

/**
 * @brief   终止显示视频流
 * @param   cam[in]   相机句柄
 * @return  无
 */
HASDK_API void HASDK_CALL HA_StopStream(struct HA_Cam* cam);

/**
 * @brief   终止显示第二路视频流的某一个窗口
 * @param   cam[in]   相机句柄
 * @return  无
 */
HASDK_API void HASDK_CALL HA_StopStreamEx1(struct HA_Cam* cam, HWND hWnd);

/**
 * @brief   终止显示第二路视频流
 * @param   cam[in]   相机句柄
 * @return  无
 */
HASDK_API void HASDK_CALL HA_StopStream1(struct HA_Cam* cam);

/**
 * @brief   视频流截图，并按传入的文件名保存图片，后缀可以为bmp，jpg，多级路径请自行建立
 * @param   cam[in]   相机句柄
 * @param   fileName[in]   文件名
 * @return  0 截图成功
 * @return  -1 截图失败
 */
HASDK_API int HASDK_CALL HA_CapImgToFile(struct HA_Cam* cam, const char* fileName);

/**
* @brief   视频流截图, 并将数据保存的内存中。内存数据为jpg
* @param   cam[in]   相机句柄
* @param   buffer[in]   buffer
* @param   bufferSize[in]  buffer长度
* @param   len[out] 数据长度
* @return  0 截图成功
* @return  -1 截图失败
*/
HASDK_API int HASDK_CALL HA_CapImgToBuffer(struct HA_Cam* cam, unsigned char* buffer, int bufferSize, int* len);


/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_Trigger(struct HA_Cam* cam, int usrParam);


/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetWhiteList(struct HA_Cam* cam, struct HA_AllowList* allowList, int listNum);


/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_GetWhiteList(struct HA_Cam* cam, struct HA_AllowList* allowList, int maxNum, int* listNum);


/**
* 废弃  
*/
HASDK_API int HASDK_CALL HA_GetWhiteListByPage(struct HA_Cam* cam, int pageNum, int recordNumPerPage, struct HA_AllowList* allowList, int* listNum, int* totalPages);


/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_ClearWhiteList(struct HA_Cam* cam);


/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_InsertWhiteList(struct HA_Cam* cam, struct HA_AllowList* wList);


/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_UpdateWhiteListByPlate(struct HA_Cam* cam, struct HA_AllowList* wList);


/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_DeleteWhiteListByPlate(struct HA_Cam* cam, const char* plate);


/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_SearchWhiteListByPlate(struct HA_Cam* cam, const char* plate, struct HA_AllowList* wList);


/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_GetWhiteListCount(struct HA_Cam* cam);


/**
 * 废弃      
 */
HASDK_API int HASDK_CALL HA_GetSystemVersion(struct HA_Cam* cam, struct VERSION* version);

/**
 * @brief   设置语音拼接方式
 * @param   cam[in]   相机句柄
 * @param   splice[in] 拼接方式 语音将按照splice[0]-splice[1]-splice[2]-splice[3] 拼接语音 
 * 拼接内容参见 enum SpeechSplicesFlag 
 * @return  0 设置成功
 * @return  <0 设置失败        
 */
HASDK_API int HASDK_CALL HA_SetSpeechSplice(struct HA_Cam *cam,char splice[4]);

/**
 * @brief   获取语音拼接方式
 * @param   cam[in]   相机句柄
 * @param   splice[out] 拼接方式 4字节 语音按照splice[0]-splice[1]-splice[2]-splice[3] 拼接语音 
 * 拼接内容参见 enum SpeechSplicesFlag 
 * @return  0 获取成功
 * @return  <0 获取失败        
 */
HASDK_API int HASDK_CALL HA_GetSpeechSplice(struct HA_Cam *cam,char* splice);

/**
 * @brief   设置角色语音
 * @param   cam[in]   相机句柄
 * @param   role[in]   角色 0：普通人员。 1：白名单人员。 2：黑名单人员
 * @param   speech[in] ......23字节 自定义的角色语音 UTF8编码
 * @return  0 设置成功
 * @return  <0 设置失败        
 */
HASDK_API int HASDK_CALL HA_SetRoleSpeech(struct HA_Cam *cam,const int role,const char speech[32]);

/**
 * @brief   获取角色语音
 * @param   cam[in]   相机句柄
 * @param   role[in]   角色 0：普通人员。 1：白名单人员。 2：黑名单人员
 * @param   speech[out] ......23字节 自定义的角色语音 
 * @return  0 获取成功
 * @return  <0 获取失败        
 */
HASDK_API int HASDK_CALL HA_GetRoleSpeech(struct HA_Cam *cam,const int role,char* speech);

/**
 * 注：为兼容保留 获取人脸相机固件信息请使用HA_GetFaceSystemVersionEx   
 */
HASDK_API int HASDK_CALL HA_GetFaceSystemVersion(struct HA_Cam *cam, struct SystemVersionInfo *version);

/**
 * @brief   获取人脸相机固件信息
 * @param   cam[in]   相机句柄
 * @param   version[out] 固件版本信息
 * @return  0 获取成功
 * @return  <0 获取失败        
 */
HASDK_API int HASDK_CALL HA_GetFaceSystemVersionEx(struct HA_Cam *cam, struct SystemVersionInfo *version);

/**
 * @brief   获取相机系统时间
 * @param   cam[in]   相机句柄
 * @param   sysTime[out] 相机时间信息
 * @return  0 获取成功
 * @return  <0 获取失败        
 */
HASDK_API int HASDK_CALL HA_GetSystemTime(struct HA_Cam *cam, struct SystemTime *sysTime);

/**
 * @brief   设置相机系统时间
 * @param   cam[in]   相机句柄
 * @param   sysTime[in] 相机时间信息
 * @return  0 设置成功
 * @return  <0 设置失败        
 */
HASDK_API int HASDK_CALL HA_SetSystemTime(struct HA_Cam *cam, struct SystemTime *sysTime);

/**
 * @brief   获取双目相机图像校差参数 
            需先使用HA_RegBinocularAjustParam注册查询结果回调函数
 * @param   cam[in]   相机句柄
 * @return  0 获取成功
 * @return  <0 获取失败        
 */
HASDK_API int HASDK_CALL HA_GetBinocularCameraAjustParam(struct HA_Cam *cam);

/**
 * @brief   获取双目相机图像像差信息
 * @param   cam[in]   相机句柄
 * @param	reply[out] 像差信息
 * @return  0 获取成功
 * @return  <0 获取失败        
 */
HASDK_API int HASDK_CALL HA_GetBinocularCameraAjustReply(struct HA_Cam *cam,BinocularAjustReply* reply);

/**
 * @brief   查询所有人的注册Id 
 * @param   cam[in]             相机句柄
 * @param   PersonIdBuff[out]   存放id内存（每个id占用20字节）
 * @param   Buffsize[in]        PersonIdBuff大小
 * @param   count[out]          实际查到的id数量 （分配内存不足count会小于total）
 * @param   total[out]         注册人员总数
 * @return  0 查询成功
 * @return  <0 查询失败       
 */
HASDK_API int HASDK_CALL HA_GetAllPersonId(struct HA_Cam *cam,char*PersonIdBuff,const int Buffsize,int* count,int *total);

/**
* 废弃   
*/
HASDK_API int HASDK_CALL HA_GetSystemVersionEX(struct HA_Cam* cam, struct VERSION* version , const char* usrName, const char* password);

/**
 * 废弃             
 */
HASDK_API int HASDK_CALL HA_GetGatewayConfig(struct HA_Cam* cam, struct config_gateway* cfg);


/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetGatewayConfig(struct HA_Cam* cam, const struct config_gateway* cfg);


/**
 * 注：为兼容保留，获取系统配置参数请使用HA_GetFaceSystemCfgEx            
 */
HASDK_API int HASDK_CALL HA_GetFaceSystemCfg(struct HA_Cam* cam, struct FaceSystemConfig* cfg);

/**
 * @brief   获取人脸相机系统配置参数扩展
 * @param   cam[in]   相机句柄
 * @param   cfg[out] 卡口系统配置参数
 * @return  0 获取成功 
 * @return  <0 获取失败             
 */
HASDK_API int HA_GetFaceSystemCfgEx(struct HA_Cam* cam, struct FaceSystemConfig* cfg);

/**
 * 注：为兼容保留，设置系统配置参数请使用HA_GetFaceSystemCfgEx            
 */
HASDK_API int HASDK_CALL HA_SetFaceSystemCfg(struct HA_Cam* cam, const struct FaceSystemConfig* cfg);

/**
 * @brief   设置人脸相机配置参数
 * @param   cam[in]   相机句柄
 * @param   cfg[in] 卡口系统配置参数
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetFaceSystemCfgEx(struct HA_Cam* cam, const struct FaceSystemConfig* cfg);

/**
 * @brief   设置调度模式参数
 * @param   cam[in]   相机句柄
 * @param   cfg[in] 调度模式参数数组  
 * @param   ScheduleCount[in] 分类总数(数组个数)最多支持设置5种调度方式
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetScheduleModeCfg(struct HA_Cam* cam, const struct KindSchedule* cfg,int ScheduleCount);

/**
 * @brief   获取调度模式参数
 * @param   cam[in]   相机句柄
 * @param   cfg[out]  调度模式配置参数数组  注：为避免错误 请分配 KindSchedule cfg[5]
 * @param   ScheduleCount [out]  分类总数(数组个数)0~5  
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetScheduleModeCfg(struct HA_Cam* cam, struct KindSchedule* cfg,int* ScheduleCount);

/**
 * @brief   获取应用参数信息
 * @param   cam[in]   相机句柄
 * @param   param[out] 应用参数
 * @return  0 获取成功 
 * @return  <0 获取失败             
 */
HASDK_API int HASDK_CALL HA_GetFaceAppParam(struct HA_Cam* cam, struct FaceAppParam* param);

/**
 * @brief   设置应用参数信息
 * @param   cam[in]   相机句柄
 * @param   param[in] 应用惨数
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_SetFaceAppParam(struct HA_Cam* cam, const struct FaceAppParam* param);

/**
 * 保留           
 */
HASDK_API int HASDK_CALL HA_GetHardwareInfo(struct HA_Cam* cam, struct Hardware* info);

/**
 * 保留            
 */
HASDK_API int HASDK_CALL HA_SetHardwareInfo(struct HA_Cam* cam, const struct Hardware* info);


/**
 * @brief   获取平台接入应用参数
 * @param   cam[in]   相机句柄
 * @param   param[out] 应用参数
 * @return  0 获取成功 
 * @return  <0 获取失败             
 */
HASDK_API int HASDK_CALL HA_GetPlatformAccessParam(struct HA_Cam* cam, struct PlatformAccess* param);

/**
 * @brief   设置平台接入应用参数
 * @param   cam[in]   相机句柄
 * @param   param[out] 应用参数
 * @return  0 获取成功 
 * @return  <0 获取失败             
 */
HASDK_API int HASDK_CALL HA_SetPlatformAccessParam(struct HA_Cam* cam, struct PlatformAccess* param);

/**
 * @brief   平台接入人像库同步 
 * @brief   平台接入时清除相机人脸库并从并从云端重新同步
 * @param   cam[in]   相机句柄
 * @return  0 同步成功 
 * @return  <0 同步失败             
 */
HASDK_API int HASDK_CALL HA_PlatformAcSyn(struct HA_Cam* cam);

/**
 * @brief   获取闸机开闸类型
 * @param   cam[in]   相机句柄
 * @param   type[out] 闸机控制类型 0继电器， 1韦根
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetGatewayControlType(struct HA_Cam* cam, int *type);

/**
 * @brief   设置闸机开闸类型
 * @param   cam[in]   相机句柄
 * @param   type[in] 闸机控制类型 0继电器， 1韦根
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_SetGatewayControlType(struct HA_Cam* cam, int type);

/**
 * @brief   获取4G信号状态
 * @param   cam[in]   相机句柄
 * @param   info[out] 4G信号状态
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_Get4GInfo(struct HA_Cam* cam, struct FourthGInfo* info);

/**
 * @brief   获取远程升级服务器参数
 * @param   cam[in]   相机句柄
 * @param   param[out] 服务器参数
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_GetUpdataServerParam(struct HA_Cam* cam, struct UpdataServerParam* param);

/**
 * @brief   设置远程升级服务器参数
 * @param   cam[in]   相机句柄
 * @param   param[in] 服务器参数
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_SetUpdataServerParam(struct HA_Cam* cam, const struct UpdataServerParam* param);

/**
 * @brief   相机ping指定网址 需注册 HA_RegCamPingCb 回调函数
 * @param   cam[in]   相机句柄
 * @param   url_ip[in] 网址 url或者ip地址
 * @param   timeout[in] ping最长执行时间 超过此时间会中断停止Ping命令 单位：秒 最大10S
 * @param   times[in] 发包次数  最大10次
 * @return  0 网址连通              
 * @return  <0 网址无响应 
 */
HASDK_API int HASDK_CALL HA_CamPing(struct HA_Cam* cam, char* url_ip,int timeout);

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_GetAlarmIoNum(struct HA_Cam* cam, int *IoNum);

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetAlarmIoNum(struct HA_Cam* cam, int IoNum);

/**
 * @brief   获取闸机继电器闭合持续时间
 * @param   cam[in]   相机句柄
 * @param   duration[out] 继电器闭合持续时间(500-5000ms)
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetAlarmDuration(struct HA_Cam* cam, int *duration);

/**
 * @brief   设置闸机继电器闭合持续时间
 * @param   cam[in]   相机句柄
 * @param   duration[in] 继电器闭合持续时间(500-5000ms)
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_SetAlarmDuration(struct HA_Cam* cam, int duration);

/**
 * @brief   获取闸机韦根类型
 * @param   cam[in]   相机句柄
 * @param   type[out] 韦根类型 枚举类型为WG26,WG34, WG36, WG44，目前只支持WG26, WG34
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetWiegandType(struct HA_Cam* cam, int *type);

/**
 * @brief   设置闸机韦根类型
 * @param   cam[in]   相机句柄
 * @param   type[in] 韦根类型 枚举类型为WG26,WG34, WG36, WG44，目前只支持WG26, WG34
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_SetWiegandType(struct HA_Cam* cam, int type);

/**
 * @brief   获取闸机韦根发行码，wg36 wg44需要此选项
 * @param   cam[in]   相机句柄
 * @param   dcode[out] 韦根发型码
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetWiegandDcode(struct HA_Cam* cam, int *dcode);

/**
 * @brief   设置闸机韦根发行码，wg36 wg44需要此选项
 * @param   cam[in]   相机句柄
 * @param   dcode[in] 韦根发型码
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_SetWiegandDcode(struct HA_Cam* cam, int dcode);

/**
 * @brief   获取闸机门禁公共卡号
 * @param   cam[in]   相机句柄
 * @param   cardNo[out] 门禁公共卡号
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetWiegandPublicCardNO(struct HA_Cam* cam, unsigned int *cardNo);

/**
 * @brief   设置闸机门禁公共卡号
 * @param   cam[in]   相机句柄
 * @param   cardNo[in] 门禁公共卡号
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_SetWiegandPublicCardNO(struct HA_Cam* cam, unsigned int cardNo);

/**
 * @brief   获取自动生成卡号时，韦根卡号范围最小值 
 * @param   cam[in]   相机句柄
 * @param   cardNoMin[out] 最小卡号
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetWiegandAutoCardNoMin(struct HA_Cam* cam, unsigned int *cardNoMin);

/**
 * @brief   设置自动生成卡号时，韦根卡号范围最小值 
 * @param   cam[in]   相机句柄
 * @param   cardNoMin[in] 最小卡号
 * @return  0 设置成功              
 * @return  <0 设置失败 
 */
HASDK_API int HASDK_CALL HA_SetWiegandAutoCardNoMin(struct HA_Cam* cam, unsigned int cardNoMin);

/**
 * @brief   获取自动生成卡号时，韦根卡号范围最大值 
 * @param   cam[in]   相机句柄
 * @param   cardNoMin[out] 最大卡号
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetWiegandAutoCardNoMax(struct HA_Cam* cam, unsigned int *cardNoMax);

/**
 * @brief   设置自动生成卡号时，韦根卡号范围最大值 
 * @param   cam[in]   相机句柄
 * @param   cardNoMax[in] 最大卡号
 * @return  0 设置成功              
 * @return  <0 设置失败 
 */
HASDK_API int HASDK_CALL HA_SetWiegandAutoCardNoMax(struct HA_Cam* cam, unsigned int cardNoMax);

/**
 * @brief   获取相机工作模式
 * @param   cam[in]   相机句柄
 * @param   work_mode[out] 相机工作模式。1：自动模式 2：在线模式 3：离线模式
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetCameraWorkMode(struct HA_Cam* cam, unsigned char *work_mode);

/**
 * @brief   设置相机工作模式
 * @param   cam[in]   相机句柄
 * @param   work_mode[in] 相机工作模式。1：自动模式 2：在线模式 3：离线模式
 * @return  0 设置成功              
 * @return  <0 设置失败 
 */
HASDK_API int HASDK_CALL HA_SetCameraWorkMode(struct HA_Cam* cam, unsigned char work_mode);

/**
 * @brief   获取相机gpio工作状态
 * @param   cam[in]   相机句柄
 * @param   state[out] gpio状态。1：常开模式 0：常闭模式
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetGpioWorkState(struct HA_Cam* cam, unsigned char *state);

/**
 * @brief   设置相机gpio工作状态
 * @param   cam[in]   相机句柄
 * @param   state[in] gpio状态。1：常开模式 0：常闭模式
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_SetGpioWorkState(struct HA_Cam* cam, unsigned char state);
/*
 * @brief   获取相机诊断信息
 * @param   cam[in]   相机句柄
 * @param   json[out] 获取到诊断信息 至少分配 1024*6；
 * @param   jsonLen[out] 诊断信息长度
 * @return  0 获取成功              
 * @return  <0 获取失败
*/
HASDK_API int HASDK_CALL HA_GetReq_DiaGgnose(struct HA_Cam* cam,char* json,int *jsonLen);

/**
 * @brief   获取相机gpio输入类型
 * @param   cam[in]   相机句柄
 * @param   type[out] gpio输入类型， 参考枚举类型GpioInType
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetGpioInputType(struct HA_Cam* cam, int *type);

/**
 * @brief   设置相机gpio输入类型
 * @param   cam[in]   相机句柄
 * @param   type[in] gpio输入类型， 参考枚举类型GpioInType
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_SetGpioInputType(struct HA_Cam* cam, int type);

/**
 * @brief   获取相机比对模式
 * @param   cam[in]   相机句柄
 * @param   mode[out]   比对类型， 参考枚举类型MatchMode
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetMatchMode(struct HA_Cam* cam, unsigned char *mode);

/**
 * @brief   设置相机人证比对模式
 * @param   cam[in]   相机句柄
 * @param   mode[in]  比对类型， 参考枚举类型MatchMode
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_SetMatchMode(struct HA_Cam* cam, unsigned char mode);

/**
 * @brief   设置姓名隐私模式
 * @param   cam[in]   相机句柄
 * @param   enable[in] 0:打开  !0:关闭 打开后相机显示解码仅显示头个字符 剩余字符由“*”代替 
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_SetNamePrivacy(struct HA_Cam* cam, char enable);

/**
 * @brief   获取注册人员到提醒取时间
 * @param   cam[in]   相机句柄
 * @param   time[out] 注册人员即将到期提醒时间 单位 S 注: (有效时间 - alarm_expire) 至有效时间 内提醒
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_GeteExpireAlarm(struct HA_Cam* cam, unsigned int* time);

/**
 * @brief   设置注册人员到期醒取时间
 * @param   cam[in]   相机句柄
 * @param   time[in] 注册人员即将到期提醒时间 单位 S 注: (有效时间 - alarm_expire) 至有效时间 内提醒
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_SeteExpireAlarm(struct HA_Cam* cam, unsigned int time);

/**
 * @brief   获取相机gpio输入开关
 * @param   cam[in]   相机句柄
 * @param   enable[out] gpio输入开关 0：关 !0：开
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetGpioInputEnable(struct HA_Cam* cam, char *enable);

/**
 * @brief   设置相机gpio输入类型
 * @param   cam[in]   相机句柄
 * @param   enable[in] gpio输入开关 0：关 !0：开
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_SetGpioInputEnable(struct HA_Cam* cam, char enable);

/**
 * @brief   设置相机io联动
 * @param   cam[in]   相机句柄
 * @param   enable[out] 是否联动 0：关 !0：开
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetGpioLinkage(struct HA_Cam* cam, char* enable);

/**
 * @brief   获取相机io联动
 * @param   cam[in]   相机句柄
 * @param   enable[in] 是否联动 0：关 !0：开
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_SetGpioLinkage(struct HA_Cam* cam, char enable);

/**
 * @brief   获取人员聚类开关，人员聚类：指对通过的人进行聚类，以便无感录入
 * @param   cam[in]   相机句柄
 * @param   enable[out] 人员聚类开关
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetClusterEnable(struct HA_Cam* cam, unsigned char *enable);

/**
 * @brief   设置人员聚类开关，人员聚类：指对通过的人进行聚类，以便无感录入
 * @param   cam[in]   相机句柄
 * @param   enable[out] 人员聚类开关
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_SetClusterEnable(struct HA_Cam* cam, unsigned char enable);

/**
 * @brief   获取人员的最大聚类次数，超过该次数就自动注册到相机
 * @param   cam[in]   相机句柄
 * @param   times[out] 人员最大聚类次数
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetMaxClusterTimes(struct HA_Cam* cam, unsigned char *times);

/**
 * @brief   设置人员的最大聚类次数，超过该次数就自动注册到相机
 * @param   cam[in]   相机句柄
 * @param   times[out] 人员最大聚类次数
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_SetMaxClusterTimes(struct HA_Cam* cam, unsigned char times);

/**
 * @brief   获取云同步参数 目前只支持webservice协议
 * @param   cam[in]   相机句柄
 * @param   sync_param[out] 注册图像同步参数
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetRegImageSync(struct HA_Cam* cam, struct RegImageSyncParam* sync_param);


/**
 * @brief   设置云同步参数 目前只支持webservice协议
 * @param   cam[in]   相机句柄
 * @param   sync_param[in] 注册图像同步参数
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_SetRegImageSync(struct HA_Cam* cam, struct RegImageSyncParam* sync_param);

/**
 * @brief   获取计算人员通过次数的间隔时间，在该时间内人员只算通过一次 用于聚类
 * @param   cam[in]   相机句柄
 * @param   interval[out] 计算人员通过次数的间隔时间，单位：秒
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetClusterTimesInterval(struct HA_Cam* cam, unsigned int *interval);

/**
 * @brief   设置计算人员通过次数的间隔时间，在该时间内人员只算通过一次  用于聚类
 * @param   cam[in]   相机句柄
 * @param   interval[out] 计算人员通过次数的间隔时间，单位：秒
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_SetClusterTimesInterval(struct HA_Cam* cam, unsigned int interval);

/**
 * @brief   获取抓拍纪录开关
 * @param   cam[in]   相机句柄
 * @param   enable[out] 抓拍纪录开关 !0：开 0：关
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetRecorderEnable(struct HA_Cam* cam, char* enable);

/**
 * @brief   设置抓拍纪录开关
 * @param   cam[in]   相机句柄 
 * @param   enable[in] 抓拍纪录开关 !0：开 0：关
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_SetRecorderEnable(struct HA_Cam* cam, char enable);

/**
 * @brief   获取抓拍纪录断点续传开关
 * @param   cam[in]   相机句柄
 * @param   enable[out] 断点续传开关 !0：开 0：关
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetRecorderResumeEnable(struct HA_Cam* cam, char* enable);

/**
 * @brief   设置抓拍纪录断点续传开关
 * @param   cam[in]   相机句柄
 * @param   enable[in] 断点续传开关 !0：开 0：关
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_SetRecorderResumeEnable(struct HA_Cam* cam, char enable);

/**
 * @brief   获取能检测的最小人脸的大小
 * @param   cam[in]   相机句柄
 * @param   size[out] 最小人脸大小  size*size的轮廓
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetFaceDetectMinRect(struct HA_Cam* cam, unsigned int *size);

/**
 * @brief   设置能检测的最小人脸的大小
 * @param   cam[in]   相机句柄
 * @param   size[in] 最小人脸大小  size*size的轮廓
 * @return  0 设置成功              
 * @return  <0 设置失败 
 */
HASDK_API int HASDK_CALL HA_SetFaceDetectMinRect(struct HA_Cam* cam, unsigned int size);

/**
 * @brief   获取串口输入配置开关
 * @param   cam[in]   相机句柄
 * @param   index[in] 串口编号目前仅支持 HA_SERIA_RS485
 * @param   enable[out] 开关 0：关 !0：开
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetSerialConfigServiceEnable(struct HA_Cam* cam, int index, char *enable);

/**
 * @brief   设置串口输入配置开关
 * @param   cam[in]   相机句柄
 * @param   index[in] 串口编号目前仅支持 HA_SERIA_RS485
 * @param   enable[in] 开关 0：关 !0：开
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_SetSerialConfigServiceEnable(struct HA_Cam* cam, int index, char enable);

/**
 * @brief   获取大角度人脸过滤开关
 * @param   cam[in]   相机句柄
 * @param   angle[out] 过滤的最大角度
 * @param   enable[out] 开关 0：关 !0：开
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetValidAngleEnable(struct HA_Cam* cam, char *angle, char *enable);

/**
 * @brief   设置大角度人脸过滤开关
 * @param   cam[in]   相机句柄
 * @param   angle[in] 过滤的最大角度
 * @param   enable[in] 开关 0：关 !0：开
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_SetValidAngleEnable(struct HA_Cam* cam, char angle, char enable);

/**
 * @brief   获取人脸检测质量阈值开关
 * @param   cam[in]   相机句柄
 * @param   threshold[out] 检测质量阈值1~100
 * @param   enable[out] 开关 0：关 !0：开
 * @return  0 获取成功              
 * @return  <0 获取失败
 */
HASDK_API int HASDK_CALL HA_GetQvalueThresholdEnable(struct HA_Cam* cam, char *threshold, char *enable);

/**
 * @brief   设置人脸检测质量阈值开关
 * @param   cam[in]   相机句柄
 * @param   threshold[in] 检测质量阈值1~100
 * @param   enable[in] 开关 0：关 !0：开
 * @return  0 设置成功              
 * @return  <0 设置失败
 */
HASDK_API int HASDK_CALL HA_SetQvalueThresholdEnable(struct HA_Cam* cam, char threshold, char enable);

/**
 * @brief   获取人脸比对确性分数
 * @param   cam[in]   相机句柄
 * @param   score[out] 确信分数（0-100分）
 * @return  0 获取成功              
 * @return  <0 获取失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetMatchScore(struct HA_Cam* cam, int *score);

/**
 * @brief   设置人脸比对确性分数
 * @param   cam[in]   相机句柄
 * @param   score[in] 确信分数（0-100分）
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetMatchScore(struct HA_Cam* cam, int score);

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_GetOutputDelay(struct HA_Cam* cam, int *delay);

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetOutputDelay(struct HA_Cam* cam, int delay);

/**
 * @brief   获取人脸抓拍图片输出控制
 * @param   cam[in]   相机句柄
 * @param   ctl[out] 输出控制，0:未初始化 1:全景 2:特写 4:比对原型图 8：特征数据 16:调试图像（功能复选的时候，对对应数字做与操作）
 * @return  0 获取成功              
 * @return  <0 获取失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetOutputCtl(struct HA_Cam* cam, int *ctl);

/**
 * @brief   设置人脸抓拍图片输出控制
 * @param   cam[in]   相机句柄
 * @param   ctl[in] 输出控制，0:未初始化 1:全景 2:特写 4:比对原型图 8：特征数据 16:调试图像（功能复选的话，对应数字做或操作）
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetOutputCtl(struct HA_Cam* cam, int ctl);

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_GetMatchLevel(struct HA_Cam* cam, int *level);

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetMatchLevel(struct HA_Cam* cam, int level);

/**
 * @brief   获取人脸比对开关
 * @param   cam[in]   相机句柄
 * @param   enable[out] 比对开关，0:关 1:开
 * @return  0 获取成功              
 * @return  <0 获取失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetMatchEnable(struct HA_Cam* cam, int *enable);

/**
 * @brief   设置人脸比对开关
 * @param   cam[in]   相机句柄
 * @param   enable[in] 调试开关，0:关 1:开
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetMatchEnable(struct HA_Cam* cam, int enable);

/**
 * @brief   获取性别开关状态
 * @param   cam[in]   相机句柄
 * @param   enable[out]  0:关 1:开
 * @return  0 获取成功              
 * @return  <0 获取失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetSexEnable(struct HA_Cam* cam, int *enable);

/**
 * @brief   设置性别开关
 * @param   cam[in]   相机句柄
 * @param   enable[in] 0:关 1:开
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetSexEnable(struct HA_Cam* cam, int enable);


/**
 * @brief   获取年龄开关状态
 * @param   cam[in]   相机句柄
 * @param   enable[out]  0:关 1:开
 * @return  0 获取成功              
 * @return  <0 获取失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetAgeEnable(struct HA_Cam* cam, int *enable);

/**
 * @brief   设置年龄开关
 * @param   cam[in]   相机句柄
 * @param   enable[in] 0:关 1:开
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetAgeEnable(struct HA_Cam* cam, int enable);

/**
 * @brief   获取活体检测开关状态
 * @param   cam[in]   相机句柄
 * @param   enable[out]  0:关 1:开
 * @return  0 获取成功              
 * @return  <0 获取失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetAliveDetectEnable(struct HA_Cam* cam, int *enable);

/**
 * @brief   设置活体检测开关
 * @param   cam[in]   相机句柄
 * @param   enable[in] 0:关 1:开
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetAliveDetectEnable(struct HA_Cam* cam, int enable);

/**
 * @brief   设置安全帽检测开关
 * @param   cam[in]   相机句柄
 * @param   enable[in] 0:关 1:开
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetHatDetectEnable(struct HA_Cam* cam, int enable);

/**
 * @brief   获取安全帽检测开关状态
 * @param   cam[in]   相机句柄
 * @param   enable[out] 0:关 1:开
 * @return  0 获取成功              
 * @return  <0 获取失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetHatDetectEnable(struct HA_Cam* cam, int* enable);

/**
 * @brief   设置是否需带安全帽 
 * @param   cam[in]   相机句柄
 * @param   pro[in] 0:关 1:开 打开后未带安全帽将不开闸
 * @return  0 获取成功              
 * @return  <0 获取失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetProhibitSafetyhat(struct HA_Cam* cam,int pro);

/**
 * @brief   获取是否需要带安全帽 
 * @param   cam[in]   相机句柄
 * @param   pro[out] 0:关 1:开 打开后未带安全帽将不开闸
 * @return  0 获取成功              
 * @return  <0 获取失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetProhibitSafetyhat(struct HA_Cam* cam,int* pro);

/**
 * 废弃
 */

HASDK_API int HASDK_CALL HA_GetFaceAlarmEnable(struct HA_Cam* cam, int* enable);

/**
 * 废弃
 */

HASDK_API int HASDK_CALL HA_SetFaceAlarmEnable(struct HA_Cam* cam, int enable);


/**
 * @brief   获取外接显示屏亮度
 * @param   cam[in]   相机句柄
 * @param   Level[out]  亮度等级
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetLcdLightLevel(struct HA_Cam* cam, char* Level);


/**
 * @brief   设置外接显示屏亮度
 * @param   cam[in]   相机句柄
 * @param   Level[in]  亮度等级
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetLcdLightLevel(struct HA_Cam* cam, char Level);


/**
 * @brief   获取LCD显示屏显示项
 * @param   cam[in]   相机句柄
 * @param   itme[out]  显示项 参见 参见 enum LcdDisplayItem
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetLcdDisplayItems(struct HA_Cam* cam, char* item);


/**
 * @brief   设置LCD显示屏显示项
 * @param   cam[in]   相机句柄
 * @param   itme[in]  显示项 参见 参见 enum LcdDisplayItem
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetLcdDisplayItems(struct HA_Cam* cam, char itme);

/**
 * @brief   获取比对成功显示项
 * @param   cam[in]   相机句柄
 * @param   Options[out]  显示项 参见 参见 enum LcdPersonDisplayItem
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetPersonDisplayOptions(struct HA_Cam* cam, char* Options);

/**
 * @brief   设置比对成功显示项
 * @param   cam[in]   相机句柄
 * @param   Options[in]  显示项 参见 参见 enum LcdPersonDisplayItem
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetPersonDisplayOptions(struct HA_Cam* cam, char Options);

/**
 * @brief   获取镜像显示开关 
 * @param   cam[in]   相机句柄
 * @param   Enable[out]  0:关 !0:开
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetflipEnable(struct HA_Cam* cam, char* Enable);

/**
 * @brief   设置镜像显示开关 
 * @param   cam[in]   相机句柄
 * @param   Enable[in]   0:关 !0:开
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetflipEnable(struct HA_Cam* cam, char Enable);

/**
 * @brief   设置LCD显示屏UI
 * @param   cam[in]   相机句柄
 * @param   uiParam[in]  UI配置
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetLcdUI(struct HA_Cam* cam, const struct UIComponentParam* uiParam);

/**
 * @brief   设置使用动态对比分数阈值，打开后将不使用配置的对比分数阈值
 * @param   cam[in]   相机句柄
 * @param   enable[in]  0:关 1:开
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */

HASDK_API int HASDK_CALL HA_SetAutoScoreEnable(struct HA_Cam* cam, int enable);

/**
 * @brief   获取使用动态阈值开关
 * @param   cam[in]   相机句柄
 * @param   enable[out]  0:关 1:开
 * @return  0 获取成功              
 * @return  <0 获取失败 
 */
HASDK_API int HASDK_CALL HA_GetAutoScoreEnable(struct HA_Cam* cam, int* enable);

/**
 * @brief   获取人脸调试开关
 * @param   cam[in]   相机句柄
 * @param   enable[out] 比对开关，0:关 1:开
 * @return  0 获取成功              
 * @return  <0 获取失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_GetDebugEnable(struct HA_Cam* cam, int *enable);

/**
 * @brief   设置人脸调试开关
 * @param   cam[in]   相机句柄
 * @param   enable[in] 调试开关，0:关 1:开
 * @return  0 设置成功              
 * @return  <0 设置失败  配置.h并没有更新
 */
HASDK_API int HASDK_CALL HA_SetDebugEnable(struct HA_Cam* cam, int enable);

/**
 * @brief   查看深度去重复开关
 * @param   cam[in]   相机句柄
 * @param   enable[out] 去重复开关，0:关 1:开
 * @param   interval[out] 重复超时，当enable为1的时候有效
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetDereplicationgConfig(struct HA_Cam* cam, int *enable, int *timeout);

/**
 * @brief   设置深度去重复开关
 * @param   cam[in]   相机句柄
 * @param   enable[in] 深度去重复开关，0:关 1:开
 * @param   interval[in] 重复超时(1s~60s)，当enable为1的时候有效
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetDereplicationEnable(struct HA_Cam* cam, int enable, int timeout);

/**
 * @brief   查看输出图像的品质
 * @param   cam[in]   相机句柄
 * @param   quality[out] jpg图像品质[1~100]
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetOutputImageQuality(struct HA_Cam* cam, int *quality);

/**
 * @brief   设置输出图像的品质
 * @param   cam[in]   相机句柄
 * @param   quality[in] jpg图像品质[1~100]
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetOutputImageQuality(struct HA_Cam* cam, int quality);

/**
 * @brief   设置子码流参数
 * @param   cam[in]   相机句柄
 * @param   param[in] 子码流参数
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetSubCodParam(struct HA_Cam* cam, const struct SubCodParam* param);

/**
 * @brief   获取子码流参数
 * @param   cam[in]   相机句柄
 * @param   param[out] 子码流参数
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetSubCodParam(struct HA_Cam* cam,struct SubCodParam* param);

/**
 * @brief   切换解码器到子码流  
 * @param   cam[in]   相机句柄
 * @param   DecodeSwitch[in] 0:解码主码流 1:解码子码流
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SwitchDecode(struct HA_Cam* cam,int DecodeSwitch);

/**
 * @brief   查看过期自动清理开关
 * @param   cam[in]   相机句柄
 * @param   enable[out] 清理开关:关 1:开
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetAutoCleanEnable(struct HA_Cam* cam, int *enable);

/**
 * @brief   设置过期自动清理开关
 * @param   cam[in]   相机句柄
 * @param   enable[in] 清理开关，0:关 1:开
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetAutoCleanEnable(struct HA_Cam* cam, int enable);

/**
 * @brief   获取上传方式域名
 * @param   domain[out] 上传域名 注：占用128字节 
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetUploadDomain(struct HA_Cam* cam, char* domain);

/**
 * @brief   设置上传方式域名 注：仅在 HA_SetUploadConfig配置ip设为NULL时有效
 * @param   domain[in] 上传域名 注：最长128字节
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetUploadDomain(struct HA_Cam* cam, char* domain);

/**
 * @brief   查看数据上传配置
 * @param   UploadParam[in] 数据上传的参数
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetUploadConfig(struct HA_Cam* cam, struct ClientParam *UploadParam);

/**
 * @brief   设置数据上传配置
 * @param   cam[in]   相机句柄
 * @param   UploadParam[in] 数据上传的参数
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetUploadConfig(struct HA_Cam* cam, struct ClientParam *UploadParam);

/**
 * @brief   重置应用参数
 * @param   cam[in]   相机句柄
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_ResetFaceConfig(struct HA_Cam* cam);

/**
 * @brief   获取最大曝光时间
 * @param   cam[in]   相机句柄
 * @param   max_exposure[out] 最大曝光时间
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetMaxExposure(struct HA_Cam* cam, short *max_exposure);

/**
 * @brief   设置最大曝光时间
 * @param   cam[in]   相机句柄
 * @param   max_exposure[in] 最大曝光时间（0~100ms）
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetMaxExposure(struct HA_Cam* cam, short max_exposure);

/**
 * @brief   获取最大增益
 * @param   cam[in]   相机句柄
 * @param   max_gain[out] 最大增益
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetMaxGain(struct HA_Cam* cam, short *max_gain);

/**
 * @brief   设置最大增益
 * @param   cam[in]   相机句柄
 * @param   max_gain[in] 最大增益（0~40DB）
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetMaxGain(struct HA_Cam* cam, short max_gain);

/**
 * @brief   获取对比度
 * @param   cam[in]   相机句柄
 * @param   contrast[out] 对比度
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetContrast(struct HA_Cam* cam, short *contrast);

/**
 * @brief   设置对比度
 * @param   cam[in]   相机句柄
 * @param   contrast[in] 对比度0~128
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetContrast(struct HA_Cam* cam, short contrast);

/**
 * @brief   获取双目摄像图像差校正区域
 * @param   cam[in]   相机句柄
 * @param   rect[out]  图像差校正区域 (rect[3])
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetBinoCorretArea(struct HA_Cam* cam, SRect *rect);

/**
 * @brief   设置双目摄像图像差校正区域
 * @param   cam[in]   相机句柄
 * @param   rect[in]  图像差校正区域 (rect[3])
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetBinoCorretArea(struct HA_Cam* cam, SRect rect[3]);

/**
 * @brief   获取畸变校正参数
 * @param   cam[in]   相机句柄
 * @param   ldc_enable[out]  畸变校变使能 0关 非0开 为NULL表示不获取
 * @param   ldc_ratio[out]  畸变程度取值范围 [-300,500], <0对应枕形 >0对应桶形 为NULL表示不获取
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetDeformityCorret(struct HA_Cam* cam,char* ldc_enable,int* ldc_ratio);

/**
 * @brief   设置畸变校正参数
 * @param   cam[in]   相机句柄
 * @param   ldc_enable[in]  畸变校变使能 0关 非0开 为NULL表示不改变
 * @param   ldc_ratio[in]  畸变程度取值范围 [-300,500] <0对应枕形 >0对应桶形 为NULL表示不改变
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetDeformityCorret(struct HA_Cam* cam,char* ldc_enable,int* ldc_ratio);

/**
 * @brief   设置相机宽动态
 * @param   cam[in]   相机句柄
 * @param   enable[in]  开关 0:关 1：常开 2:按时间段开关 3:自动开关 
 * @param   HourSchedule[in]  打开 - 关闭 宽动态时间点段  
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetWDR(struct HA_Cam* cam,char enable,HourSchedule t_wdr);

/**
 * @brief   获取相机宽动态设置
 * @param   cam[in]   相机句柄
 * @param   enable[in]  开关 0:关 1：常开 2:按时间段开关 3:自动开关 
 * @param   HourSchedule[in]  打开 - 关闭 宽动态时间点段  
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetWDR(struct HA_Cam* cam,char* enable,HourSchedule* t_wdr);

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetLayerCSC(struct HA_Cam* cam,char value,int index);

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_GetLayerCSC(struct HA_Cam* cam,char* buf);


/**
 * @brief   获取亮度
 * @param   cam[in]   相机句柄
 * @param   brightness[out] 亮度
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetBrightness(struct HA_Cam* cam, unsigned char *brightness);

/**
 * @brief   设置亮度
 * @param   cam[in]   相机句柄
 * @param   brightness[in] 亮度0~100
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetBrightness(struct HA_Cam* cam, unsigned char brightness);

/**
 * @brief   获取饱和度
 * @param   cam[in]   相机句柄
 * @param   saturation[out] 饱和度
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetSaturation(struct HA_Cam* cam, unsigned char *saturation);

/**
 * @brief   设置饱和度
 * @param   cam[in]   相机句柄
 * @param   saturation[in] 饱和度1~255
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetSaturation(struct HA_Cam* cam, unsigned char saturation);

/**
 * @brief   获取视频旋转角度
 * @param   cam[in]   相机句柄
 * @param   rotate[out]  视频旋转角度 0:默认值 1：顺时针旋转90度 2：顺时针旋转180度 3：顺时针旋转270度
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetVideoRotate(struct HA_Cam* cam, unsigned char *rotate);

/**
 * @brief   设置视频旋转角度
 * @param   cam[in]   相机句柄
 * @param   rotate[in] 视频旋转角度 0:默认值 1：顺时针旋转90度 2：顺时针旋转180度 3：顺时针旋转270度
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetVideoRotate(struct HA_Cam* cam, unsigned char rotate);

/**
 * @brief   获取外接显示屏标题
 * @param   cam[in]   相机句柄
 * @param   screen_title[out]  外接显示屏标题 UTF8格式 最大64个字节
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetScreenOsdTitle(struct HA_Cam* cam, char *screen_title);

/**
 * @brief   设置外接显示屏标题
 * @param   cam[in]   相机句柄
 * @param   screen_title[in] 外接显示屏标题 UTF8格式 最大64个字节
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetScreenOsdTitle(struct HA_Cam* cam, char *screen_title);

/**
 * @brief   获取外网sdk服务参数(废弃) 请使用新接口HA_GetExtranetParam
 * @param   cam[in]   相机句柄
 * @param   enable[out] 0:关 !0：开
 * @return  ip[out] 服务端sdk服务地址 
 * @return  port[out] 服务端sdk服务端口   
 * @return  resv[out] 11个字节保留字段  
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetServerSdkParam(struct HA_Cam* cam, int *enable, char *ip, int *port, char *resv);

/**
 * @brief   设置外网sdk服务参数(废弃) 请使用新接口HA_GetExtranetParam
 * @param   cam[in]   相机句柄
 * @param   enable[in] 0:关 !0：开
 * @return  ip[in] 服务端sdk服务地址 
 * @return  port[in] 服务端sdk服务端口   
 * @return  resv[in] 11个字节保留字段  
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetServerSdkParam(struct HA_Cam* cam, int enable, char *ip, int port, char *resv);

/**
 * @brief   获取外网穿透参数
 * @param   cam[in]   相机句柄
 * @param   Param[out] 外网穿透参数
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetExtranetParam(struct HA_Cam* cam, ExtranetParam* Param);

/**
 * @brief   设置外网穿透参数
 * @param   cam[in]   相机句柄
 * @param   Param[in] 外网穿透参数
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetExtranetParam(struct HA_Cam* cam, ExtranetParam Param);

/**
 * @brief   获取Ntp参数
 * @param   cam[in]   相机句柄
 * @param   Param[out] ntp服务器参数
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetNtpConfig(struct HA_Cam* cam, struct NtpInfo *ntpInfo);

/**
 * @brief   设置Ntp参数
 * @param   cam[in]   相机句柄
 * @param   Param[in] ntp服务器参数
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetNtpConfig(struct HA_Cam* cam, struct NtpInfo *ntpInfo);


/**
 * @brief   获取Ntp参数拓展
 * @param   cam[in]   相机句柄
 * @param   Param[out] ntp服务器参数
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetNtpConfigEx(struct HA_Cam* cam, struct NtpInfoEx *ntpInfo);

/**
 * @brief   设置Ntp参数拓展
 * @param   cam[in]   相机句柄
 * @param   Param[in] ntp服务器参数
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetNtpConfigEx(struct HA_Cam* cam, struct NtpInfoEx *ntpInfo);


/**
 * @brief   查看网络参数配置
 * @param   cam[in]   相机句柄
 * @param   netInfo[out] 网络参数
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetNetConfig(struct HA_Cam* cam, struct SystemNetInfo *netInfo);

/**
 * @brief   设置网络参数配置
 * @param   cam[in]   相机句柄
 * @param   netInfo[in] 网络参数
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetNetConfig(struct HA_Cam* cam, struct SystemNetInfo *netInfo);

/**
 * @brief   查看网络参数配置扩展
 * @param   cam[in]   相机句柄
 * @param   netInfo[out] 网络参数
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetNetConfigEx(struct HA_Cam* cam, struct SystemNetInfoEx *netInfo);

/**
 * @brief   设置网络参数配置扩展
 * @param   cam[in]   相机句柄
 * @param   netInfo[in] 网络参数
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetNetConfigEx(struct HA_Cam* cam, struct SystemNetInfoEx *netInfo);

/**
 * @brief   注册voip
 * @param   cam[in]   相机句柄
 * @param   username[in] 用户名
 * @param   domain[in]   ip/域名
 * @param   port[in] 端口
 * @param   password[in] 密码 可为NULL
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetVoipRegister(struct HA_Cam* cam, const char* username, const char* domain, unsigned short port, const char* password);


/**
 * @brief   相机搜索WiFi列表   需注册 HA_RegSearchWiFiCb
 * @param   cam[in]   相机句柄
 * @param   ssid[in]  填NULL
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SearchWifi(struct HA_Cam* cam ,const char* ssid);

/**
 * @brief   查看已连接wifi信息  需注册 HA_RegSearchWiFiCb
 * @param   cam[in]   相机句柄
 * @param   wifiInfor[out]   wifi信息
 * @return  0 查询成功              
 * @return  <0 查询失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_WifiInfor(struct HA_Cam* cam, struct WifiSignal* wifiInfor);

/**
 * @brief   相机连接/断开wifi 注回0 仅代表相机接受此次请求  获取连接状态需注册 HA_RegWifiConnectCb
 * @param   cam[in]   相机句柄
 * @param   switchAP[in] 连接失败是否切换为AP模式，0：不切换 !0：切换 安卓调用填1 其他0
 * @param   ssid[in]   wifi名称  断开时可填NULL
 * @param   password[in]   wifi密码 断开时可填NULL
 * @param   enable[in]   连接 0:断开 !0:连接
 * @return  0 相机已接受此信息成功              
 * @return  <0 相机未处理此信息
 */
HASDK_API int HASDK_CALL HA_ConnectWifi(struct HA_Cam* cam ,char switchAP ,const char* ssid, const char* password, char enable);

/**
 * @brief   获取led灯模式
 * @param   cam[in]   相机句柄
 * @param   led_mode[out] led灯模式 1：常亮 2：自动控制 3：常闭
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetLedMode(struct HA_Cam* cam, char *led_mode);

/**
 * @brief   设置led灯模式
 * @param   cam[in]   相机句柄
 * @param   led_mode[in] led灯模式 1：常亮 2：自动控制 3：常闭
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetLedMode(struct HA_Cam* cam, char led_mode);

/**
 * @brief   获取led亮度
 * @param   cam[in]   相机句柄
 * @param   led_level[out] 亮度 1~100
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetLedLevel(struct HA_Cam* cam, char *led_level);

/**
 * @brief   设置led灯亮度
 * @param   cam[in]   相机句柄
 * @param   led_level[in] 亮度 1~100
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetLedLevel(struct HA_Cam* cam, char led_level);

/**
 * @brief   获取led灯亮度阈值
 * @param   cam[in]   相机句柄
 * @param   led_threshold[out] led亮度阈值
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetLedThreshold(struct HA_Cam* cam, char *led_threshold);

/**
 * @brief   设置led灯亮度阈值
 * @param   cam[in]   相机句柄
 * @param   led_threshold[in] led亮度阈值 0~255
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetLedThreshold(struct HA_Cam* cam, char led_threshold);

/**
 * @brief   获取检测区域
 * @param   cam[in]   相机句柄
 * @param   rect[out] 显示区域轮廓
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetDetectRect(struct HA_Cam* cam, struct ha_rect* rect);

/**
 * @brief   设置检测区域
 * @param   cam[in]   相机句柄
 * @param   rect[in] 显示区域轮廓
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetDetectRect(struct HA_Cam* cam, struct ha_rect* rect);

/**
 * @brief   获取485输出协议编号
 * @param   cam[in]   相机句柄
 * @param   rs485_protocal_no[out] rs485输出协议编号 0：表示关 人脸RS485输出协议.xlsx
 * @return  0 获取成功              
 * @return  <0 获取失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_GetRS485ProtocalNo(struct HA_Cam* cam, char *rs485_protocal_no);

/**
 * @brief   设置485输出协议编号
 * @param   cam[in]   相机句柄
 * @param   rs485_protocal_no[in] rs485输出协议编号 0：表示关  人脸RS485输出协议.xlsx
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码
 */
HASDK_API int HASDK_CALL HA_SetRS485ProtocalNo(struct HA_Cam* cam, char rs485_protocal_no);







/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_GetAuthInfo(HA_Cam* cam, const char *user_name, const char *passwd, struct AuthParam *authInfo);

/**
* @brief   获取登录认证开关状态
* @param   cam[in]   相机句柄
* @param   enable[out]   登录认证开关 0：关 1：开
* @return  0 获取成功
* @return  <0 获取失败
*/
HASDK_API int HASDK_CALL HA_GetAuthEnableInfo(HA_Cam* cam, int *enable);

/**
* @brief   修改登录认证信息
* @param   cam[in]   相机句柄
* @param   user_name[in] 原用户名
* @param   passwd[in]   原密码
* @param   authInfo[out] 登录认证信息
* @return  0 获取成功
* @return  <0 获取失败
*/
HASDK_API int HASDK_CALL HA_SetAuthInfo(HA_Cam* cam, const char *user_name, const char *passwd, struct AuthParam *authInfo);

/**
* @brief   设置SDK密码，未设置则使用默认密码 
* @param   password[in] SDK密码  注：最长48个字符
* @return  0 设置成功
* @return  <0 设置失败
*/
HASDK_API int HASDK_CALL HA_SetSDKPassword(const char* password);

/**
* @brief   开启相机SDK密码，未设置则使用默认密码
* @param   cam[in]   相机句柄
* @param   password[in] SDK密码  注：最长48个字符
* @return  0 设置成功
* @return  <0 设置失败
*/
HASDK_API int HASDK_CALL HA_SetCamSDKPassword(struct HA_Cam* cam,const char* password);

/**
* @brief   相机功能授权
* @param   cam[in]   相机句柄
* @param   number[in] 功能编号 0:单目活检功能 2:TTS 授权 4:山东聊城
* @param   data[in] 许可证数据
* @param   size[in] 许可证数据长度
* @return  0 授权成功
* @return  <0 获取失败 见错误码
*/
HASDK_API int HASDK_CALL HA_FunctionAuth(struct HA_Cam* cam, short number, const char* data,short size);


/**
* @brief   查询相机功能授权状态
* @param   cam[in]   相机句柄
* @param   number[in] 功能编号 0:单目活检功能
* @return  !0:已授权
* @return  0 未授权 
*/
HASDK_API int HASDK_CALL HA_AuthState(struct HA_Cam* cam, short number);
/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_GetGatewayOfflineMode(struct HA_Cam* cam, int* offlineFlag);


/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetGatewayOfflineMode(struct HA_Cam* cam, int offlineFlag);


/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetOfflinePlateInfoCb(struct HA_Cam* cam, HA_PlateInfoCb_t cb, int usrParam);

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetTransfferOffline(struct HA_Cam* cam, int transFlag);


/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_GetTransfferOffline(struct HA_Cam* cam, int* transFlag);

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetIOOutput(struct HA_Cam* cam, int index, int state);

/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_SetIOOutputAuto(struct HA_Cam* cam, int index, int timeDuration);


/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetAlarm(struct HA_Cam* cam, int open);

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetIOState(struct HA_Cam* cam, int index, int state);

/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_SetAlarmAuto(struct HA_Cam* cam, int index, int timeDuration);

/**
* @brief   触发白名单报警，强制模式开闸
* @param   cam[in]   相机句柄
* @param   inout[in] 输入输出状态，1输入 2输出（目前只支持输出）
* @param   onoff[in] 1：通 0：断（目前只支持通，断由相机固定延时后断开）
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_WhiteListAlarm(struct HA_Cam *cam, int inout, int onoff);

/**
* @brief   触发黑名单报警,强制模式开闸
* @param   cam[in]   相机句柄
* @param   inout[in]  输入、输出 1输入 2输出
* @param   onoff[in] 开关 1连通 0断开
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_BlackListAlarm(struct HA_Cam *cam, int inout, int onoff);

/**
* @brief   触发韦根开闸,强制模式开闸
* @param   cam[in]   相机句柄
* @param   wiegand_no[in]  韦根卡号
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_WiegandAlarm(struct HA_Cam *cam, unsigned int wiegand_no);

/**
* @brief   触发白名单报警,需指定开闸模式
* @param   cam[in]   相机句柄
* @param   inout[in]  输入、输出 1输入 2输出
* @param   onoff[in] 开关 1连通 0断开
* @param   alarm_mode[in] 控制方式。0：强制方式 1：非强制方式,强制方式将强制输出信号到设备。
                  非强制方式是否输出信号到设备取决于设备是否使能。
* @param   person_id[in] 开闸的人员id，用于相机记录开闸记录
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_WhiteListAlarmEx(struct HA_Cam *cam, int inout, int onoff, unsigned char alarm_mode, unsigned char *person_id);

/**
* @brief   触发黑名单报警,需指定开闸模式
* @param   cam[in]   相机句柄
* @param   inout[in]  输入、输出 1输入 2输出
* @param   onoff[in] 开关 1连通 0断开
* @param   alarm_mode[in] 控制方式。0：强制方式 1：非强制方式,强制方式将强制输出信号到设备。
                  非强制方式是否输出信号到设备取决于设备是否使能。
* @param   person_id[in] 开闸的人员id，用于相机记录开闸记录
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_BlackListAlarmEx(struct HA_Cam *cam, int inout, int onoff, unsigned char alarm_mode, unsigned char *person_id);

/**
* @brief   触发韦根开闸,需指定开闸模式
* @param   cam[in]   相机句柄
* @param   wiegand_no[in]  韦根卡号
* @param   alarm_mode[in] 控制方式。0：强制方式 1：非强制方式,强制方式将强制输出信号到设备。
                  非强制方式是否输出信号到设备取决于设备是否使能。
* @param   person_id[in] 开闸的人员id，用于相机记录开闸记录
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_WiegandAlarmEx(struct HA_Cam *cam, unsigned int wiegand_no, unsigned char alarm_mode, unsigned char *person_id);

/**
* @brief   GPIO控制
* @param   cam[in]   相机句柄
* @param   port[in]  GPIO端口号 取值为0时表示韦根设备。其它取值表示GPIO设备。
* @param   inout[in] 输入输出状态，1输入 2输出（目前只支持输出）
* @param   onoff[in] 1：通 0：断（目前只支持通，断由相机固定延时后断开）
* @param   resv[in] 
           resv[0]控制方式。0:测试模式 1：强制方式 2：非强制方式,强制方式将强制输出信号到设备。
                  非强制方式是否输出信号到设备取决于设备是否使能。
           resv[1-4]-->uint 韦根协议门禁卡号。 
           resv[5-24]-->uint 开闸的人员id
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_SetGPIO(struct HA_Cam* cam, int port, int inout, int onoff, char *resv);

/**
* @brief   GPIO控制
* @param   cam[in]   相机句柄
* @param   port[in]  GPIO端口号 取值为0时表示韦根设备。其它取值表示GPIO设备。
* @param   inout[in] 输入输出状态，1输入 2输出（目前只支持输出）
* @param   onoff[in] 1：通 0：断（目前只支持通，断由相机固定延时后断开）
* @param   resv[in] 
           resv[0]控制方式。0:测试模式 1：强制方式 2：非强制方式,强制方式将强制输出信号到设备。
                  非强制方式是否输出信号到设备取决于设备是否使能。
           resv[1-4]-->uint 韦根协议门禁卡号。 
           resv[5-24]-->uint 开闸的人员id
		   resv[25-32]-->uint 韦根协议门禁卡号8位长版
		   resv[33-40]--> 保留
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_SetGPIOEx(struct HA_Cam* cam, int port, int inout, int onoff, char *resv);

/**
* @brief   播放音频。注：只支持wav格式声音数据(压缩参数：A-Law, 8000Hz,64kbps,mono)
* @param   cam[in]   相机句柄
* @param   audio[in]  音频数据
* @param   len[in]  音频数据长度       
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_PlayAudio(struct HA_Cam* cam, const char* audio, int len);


/**
* @brief   将文字转换为语音并播放
* @param   cam[in]  相机句柄
* @param   txt[in]  要播放的文字 注:最大一次播放88个汉字 使用UTF8编码
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_TTSPlayAudio(struct HA_Cam* cam, const char* txt);


/**
 * @brief   注册读透明串口
 * @param   cb[in] 透明串口返回数据回调
 * @param   usrParam[in] 用户参数
 * @return  0 成功
 * @return  <0 失败
 */
HASDK_API int HASDK_CALL HA_RegReadTSerialCb(HA_ReadTSerialCb_t cb, int usrParam);


/**
 * @brief   注册读透明串口
 * @param   cb[in] 透明串口返回数据回调
 * @param   usrParam[in] 用户参数
 * @return  0 成功
 * @return  <0 失败
 */
HASDK_API int HASDK_CALL HA_RegReadTSerialCbEx(HA_Cam* cam, HA_ReadTSerialCb_t cb, int usrParam);

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_RegReadGpioCbEx(HA_Cam* cam, HA_ReadGpioCb_t cb, int usrParam);

/**
 * @brief   注册Gpio
 * @param   cb[in] Gpio/WG返回数据回调  
 * @param   usrParam[in] 用户参数
 * @return  0 成功
 * @return  <0 失败
 */
HASDK_API int HASDK_CALL HA_RegGpioInputCb(HA_Cam* cam, HA_GpioInputCb_t cb, void* usrParam);

/**
 * @brief   注册WG卡号输入回调
 * @param   cb[in] WG卡号输入返回数据回调 目前仅支持WG66
 * @param   usrParam[in] 用户参数
 * @return  0 成功
 * @return  <0 失败
 */
HASDK_API int HASDK_CALL HA_RegWGInputCb(HA_Cam* cam, HA_WGInputCb_t cb, void* usrParam);

/**
 * @brief   获取透明串口参数
 * @param   cam[in]   相机句柄
 * @param   index[in] 第N路串口,目前只支持 HA_SERIA_RS485  HA_SERIA_RS232
 * @param   baudrate[out] 波特率 
 * @param   baudrate:只能为以下值：1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200, 128000, 256000
 * @param   parity[out] 校验位。只能为0，无校验位
 * @param   databit[out] 数据位，只能为5，6，7，8
 * @param   stopbit[out] 停止位，只能为1，2
 * @return  0 成功
 * @return  <0 失败
 */
HASDK_API int HASDK_CALL HA_GetTSerial(struct HA_Cam* cam, int index, int* baudrate, int* parity, int* databit, int* stopbit);



/**
 * @brief   打开透明串口
 * @param   cam[in]   相机句柄
 * @param   index[in] 第N路串口,目前只支持 HA_SERIA_RS485  HA_SERIA_RS232
 * @param   baudrate[in] 波特率 
 * @param   baudrate:只能为以下值：1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200, 128000, 256000
 * @param   parity[in] 校验位。0:none, 1:odd, 2:even, 3:mark, 4:space
 * @param   databit[in] 数据位，只能为5，6，7，8
 * @param   stopbit[in] 停止位，只能为1，2
 * @return  0 成功
 * @return  <0 失败
 */
HASDK_API int HASDK_CALL HA_OpenTSerial(struct HA_Cam* cam, int index, int baudrate, int parity, int databit, int stopbit);


/**
 * @brief   写透明串口
 * @param   cam[in]   相机句柄
 * @param   index[in] 第N路串口,目前只支持 HA_SERIA_RS485  HA_SERIA_RS232
 * @param   data[in] 数据
 * @param   size[in] 数据长度
 * @return  0 成功
 * @return  <0 失败
 */
HASDK_API int HASDK_CALL HA_WriteTSerial(struct HA_Cam* cam, int index, const unsigned char* data, int size);


/*
 * 保留
 */
HASDK_API int HASDK_CALL HA_CloseTSerial(struct HA_Cam* cam, int index);


//===========================透明串口==============================end


//===========================相机参数=============================begin
/*
 * @brief   获取相机参数

 * 预留 
 */
HASDK_API int HASDK_CALL HA_GetCamParam(struct HA_Cam* cam, struct CamCtrl* ctrl);

/**
*/
HASDK_API void HASDK_CALL HA_RebootCam(struct HA_Cam* cam);

/***                 
*/
HASDK_API void HASDK_CALL HA_SaveCamParam(struct HA_Cam* cam);

/*
 * 废弃    
 */
HASDK_API void HASDK_CALL HA_SetAutoCtrl(struct HA_Cam* cam, struct CamCtrlAutoCtrl* ctrl);

/*
 * 废弃     
 */
HASDK_API void HASDK_CALL HA_SetImageEnhance(struct HA_Cam* cam, struct CamCtrlImageEnhance* en);

/**
* 废弃
*/
HASDK_API void HASDK_CALL HA_SetSysTime(struct HA_Cam* cam, int time);

/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_GetSysTime(struct HA_Cam* cam, int* time);

/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_SetSysTimeEx(struct HA_Cam* cam, int year, int month, int day, int hour, int minute, int second);


/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_GetSysTimeEx(struct HA_Cam* cam, int* year, int* month, int* day, int* hour, int* minute, int* second);

/* 
*/
HASDK_API void HASDK_CALL HA_SetJpegQ(struct HA_Cam* cam, int q);


/*
 * 废弃
 */
HASDK_API void HASDK_CALL HA_SetH264(struct HA_Cam* cam, int w, int h, int bitrate);


//相机PTZ控制**  镜头调节
HASDK_API int HASDK_CALL HA_ZoomUpStart(struct HA_Cam* cam);
HASDK_API int HASDK_CALL HA_ZoomUpStop(struct HA_Cam* cam);
HASDK_API int HASDK_CALL HA_ZoomDownStart(struct HA_Cam* cam);
HASDK_API int HASDK_CALL HA_ZoomDownStop(struct HA_Cam* cam);

HASDK_API int HASDK_CALL HA_FocusUpStart(struct HA_Cam* cam);
HASDK_API int HASDK_CALL HA_FocusUpStop(struct HA_Cam* cam);
HASDK_API int HASDK_CALL HA_FocusDownStart(struct HA_Cam* cam);
HASDK_API int HASDK_CALL HA_FocusDownStop(struct HA_Cam* cam);

//只移动一步
HASDK_API int HASDK_CALL HA_ZoomUp(struct HA_Cam* cam);
HASDK_API int HASDK_CALL HA_ZoomDown(struct HA_Cam* cam);

HASDK_API int HASDK_CALL HA_FocusUp(struct HA_Cam* cam);
HASDK_API int HASDK_CALL HA_FocusDown(struct HA_Cam* cam);

HASDK_API int HASDK_CALL HA_FocusAndZoomCtl(struct HA_Cam* cam, int ptzCtl, int ctlMode);

/*
* @brief   视频流控制 默认开
* @param   cam[in] 相机句柄
* @param   flag[in] 0关闭 非0 打开
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_LiveStreamCtl(struct HA_Cam* cam, int flag);


//===========================相机参数=============================end

//废弃
HASDK_API int HASDK_CALL HA_GetCustomerSN(struct HA_Cam* cam, char* sn, int* SNSize);

/*
* @brief   注入用户校验码
* @param   cam[in] 相机句柄
* @param   auth[in] 校验码数据
* @param   size[in] 校验码长度
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_WriteCustomerAuthCode(struct HA_Cam* cam, char* auth, int size);

/*
* @brief   读取用户校验码
* @param   cam[in] 相机句柄
* @param   auth[out] 校验码数据
* @param   size[out] 校验码长度
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_ReadCustomerAuthCode(struct HA_Cam* cam, char* auth, int* size);


/*
* @brief   Jpeg编码函数
* @param   pRgbBuffer[in]   图像rgb原始数据
* @param   dwWidth[in] 图像宽
* @param   dwHeight[in] 图像高
* @param   pJpgBuffer[out] 存放jpeg的buffer
* @param   dwJpgSize[out] 返回jpg长度
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_EncodeJpeg(const unsigned char* pRgbBuffer,unsigned long dwWidth,unsigned long dwHeight,unsigned char* pJpgBuffer,unsigned int *dwJpgSize);


/*
* @brief   Jpeg解码函数
* @param   srcJpg[in]   jpg图像数据
* @param   srcJpgLen[in] jpg图像长度
* @param   desRgb[out] 解码后的图像数据
* @param   jpgW[out] 图像宽
* @param   jpgH[out] 图像高
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_DecodeJpeg(const unsigned char* srcJpg, int srcJpgLen, unsigned char* desRgb, unsigned int* jpgW, unsigned int* jpgH);

/*
* @brief   解析Jpeg尺寸
* @param   srcJpg[in]   jpg图像数据
* @param   srcJpgLen[in] jpg图像长度
* @param   jpgW[out] 图像宽
* @param   jpgH[out] 图像高
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_DecodeJpgSize(const unsigned char* srcJpg, int srcJpgLen, unsigned int* jpgW, unsigned int* jpgH);

/**
* @brief   开始录像                            
* @param   cam[in]   相机句柄
* @param   sFileName[in] 录像文件路径
* @return  0 成功
* @return  <0 失败   
*/
HASDK_API int HASDK_CALL HA_SaveRealDate(HA_Cam *cam ,char *sFileName);

/**
* @brief   停止录像
* @param   cam[in]   相机句柄
* @return  0 成功
* @return  <0 失败                              
*/
HASDK_API int HASDK_CALL HA_StopSaveRealDate(HA_Cam *cam);

/*
* @brief   保存红外图像，jpeg文件
* @param   cam[in]   相机句柄
* @param   sFileName[in] 录像文件路径
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_SaveRealDate1(HA_Cam *cam ,char *sFilePath);

/*
* @brief   停止保存红外图像
* @param   cam[in]   相机句柄
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_StopSaveRealDate1(HA_Cam *cam);

/**
* 备份当前参数为用户默认参数(保留)                  
*/
HASDK_API int HASDK_CALL HA_BackupUserDefault(HA_Cam *cam);


/**
* 恢复用户默认参数(保留)
*/
HASDK_API int HASDK_CALL HA_RestoreUserDefault(HA_Cam *cam);


/**
* 废弃                     
*/
HASDK_API int HASDK_CALL HA_RestorMannuFDefalut(HA_Cam *cam);

/*
* @brief   查询SD卡状态信息               
* @param   cam[in]   相机句柄
* @param   hasSDCard[out] 是否有SD卡
* @param   totalSize[out] 有SD卡时有效，单位MB
* @param   usedSize[out] 有SD卡时有效，单位MB
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_QuerySDCardInfo(HA_Cam* cam, int* hasSDCard, int* totalSize, int* usedSize);

/*
* @brief   查询相机储存信息               
* @param   cam[in]   相机句柄
* @param   infor[in]  相机容量信息
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_QuerySDCardInfoEx(HA_Cam* cam, MemoryInfor* infor);

/**
* @brief   格式化SD卡格式化成FAT32，发送命令成功，此函数立即返回。但并不代表相机已格式化SD卡完成
* @brief   SD卡格式化完成判定方法：可定时查询SD卡状态信息，如果totalSize和之前的一致。则认为完成
* @brief   SD卡格式化大致时间：16G需要2分钟左右
* @param   cam[in]   相机句柄
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_FormatSDCard(HA_Cam *cam);

/**
* @brief   格式化EMMC内存，发送命令成功，此函数立即返回。但并不代表相机已格式化SD卡完成
* @brief   格式化大致时间：16G需要2分钟左右
* @param   cam[in]   相机句柄
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_FormatEMMC(HA_Cam *cam);


/**
* @brief   获取厂家内置相机的音频列表
* @param   cam[in]   相机句柄            
* @param   items[out]   音频结构数组
* @param   itemBufNum[in]   音频结构数组数目
* @param   itemNum[out]   返回获取到的音频数目
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_GetAudioList(HA_Cam *cam, struct AudioItem* items, int itemBufNum, int* itemNum);

/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_TestAudioItem(HA_Cam *cam,  int audioId);   

/**
* @brief   播放厂家内置相机的音频文件
* @param   cam[in]   相机句柄
* @param   items[in]   音频文件名，HA_GetAudioList函数中获得
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_TestAudioItemByName(HA_Cam *cam, const struct AudioItem* items);

/**
* @brief   设置默认使用的音频文件
* @param   cam[in]   相机句柄
* @param   audioId[in]   音频id，HA_GetAudioList函数中获得
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_SetAudioDefault(HA_Cam *cam,  int audioId);

/**
* @brief   获取相机播放音量
* @param   cam[in]   相机句柄
* @param   audio_volume[out] 音量 0~100
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_GetAudioVolume(HA_Cam *cam,  int* audio_volume);


/**
* @brief   设置相机播放音量
* @param   cam[in]   相机句柄
* @param   audio_volume[in] 音量 0~100
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_SetAudioVolume(HA_Cam *cam,  int audio_volume);

/*
* @brief   GB2312字符转UTF8
* @param   inbuf[in]   GB2312字符
* @param   inlen[in]   GB2312字符长度
* @param   outbuf[out] UTF8
* @param   outlen[in] outbuf长度
* @return  0 成功
* @return  <0 失败                  
*/
HASDK_API int HASDK_CALL HA_Gb23122Utf8(char *inbuf, int inlen, char *outbuf, int outlen);


/*
* @brief   UTF8转GB2312
* @param   inbuf[in]   UTF8字符
* @param   inlen[in]   UTF8字符长度
* @param   outbuf[out] gb2312字符buf
* @param   outlen[in] outbuf长度
* @return  0 成功
* @return  <0 失败
*/
HASDK_API int HASDK_CALL HA_Utf82Gb2312(char *inbuf, int inlen, char *outbuf, int outlen);


//清除各相机公用的所有回调函数
HASDK_API int HASDK_CALL HA_ClearAllCallbacks(struct HA_Cam* cam);


//清除相机句柄内所有的回调函数   **            
HASDK_API int HASDK_CALL HA_ClearAllCallbacksEx();

/**
 * 废弃
 */
HASDK_API int HASDK_CALL HA_SetQueryPlateInfoCb(struct HA_Cam* cam, HA_PlateInfoCb_t cb, int usrParam);



/**
*  废弃
*/
HASDK_API int HASDK_CALL HA_QueryCountByTimeAndPlate(struct HA_Cam* cam, const char *pStartTime, const char *pEndTime, const char *keyword);



/**
*  废弃
*/
HASDK_API int HASDK_CALL HA_QueryRecordByTimeAndPlate(struct HA_Cam* cam, const char *pStartTime, const char *pEndTime, const char *keyword);


/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_QueryPageRecordByTimeAndPlate(struct HA_Cam* cam, const char *pStartTime, const char *pEndTime, const char *keyword, int start, int end);



/**
*  废弃
*/
HASDK_API int HASDK_CALL HA_QueryOfflineCountByTime(struct HA_Cam* cam, const char *pStartTime, const char *pEndTime);

/**
*  废弃
*/
HASDK_API int HASDK_CALL HA_QueryPageOfflineRecordByTime(struct HA_Cam* cam, const char *pStartTime, const char *pEndTime, int start, int end);

/**
*  废弃
*/
HASDK_API int HASDK_CALL HA_QueryRecordById(struct HA_Cam* cam, int id, unsigned char* img, int* imgLen);


/**
*  废弃
*/
HASDK_API int HASDK_CALL HA_QueryOfflineRecordById(struct HA_Cam* cam, int id, unsigned char* img, int* imgLen);

/**
* @brief   设置是否需要连接相机通知
* @param   notify 0：不需要 1：需要
* @return  无
*/
HASDK_API void HASDK_CALL HA_SetNotifyConnected(int notify);


//废弃
HASDK_API void HASDK_CALL HA_RegIOStateCb(HA_Cam* cam, HA_IOStateCb_t callback, void* userParm);

//废弃
HASDK_API void HASDK_CALL HA_SetPlateLogDirectory(const char* dirFullPath);

/**
*  @brief 从相机截取一张图像
*  @param  [IN] cam 要截取的相机句柄
*  @param  [OUT] snapImage 截取的图像信息
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_Snapshot(HA_Cam* cam);

/**
*  @brief 保存bmp图像
*  @param  [IN] filename 要截取的相机句柄
*  @param  [IN] imgData 图像数据
*  @param  [IN] width 图像宽度
*  @param  [IN] height 图像高度
*  @param  [IN] cn 通道数
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API void HASDK_CALL HA_SaveBMP(const char *filename, const unsigned char* imgData, int width, int height, int cn);

/**
*  @brief 写入jpg图片到指定文件，内部不创建目录，带目录的请自行创建
*  @param  [IN] filename 文件名
*  @param  [IN] jpgBuf jpg数据
*  @param  [IN] len jpg数据长度
*  @return 返回值为0表示成功，返回-1表示失败
*/
HASDK_API int HASDK_CALL HA_SaveJpg(const char *filename, const unsigned char* jpgBuf, int len);

/**
 * @brief   重启相机  
 * @param   cam[in]   相机句柄   
 * @return  返回值为0表示成功，返回<0表示失败
 */
HASDK_API int HASDK_CALL HA_SystemReboot(HA_Cam* cam);

/**
 * @brief   重启相机应用程序
 * @param   cam[in]   相机句柄
 * @return  返回值为0表示成功，返回<0表示失败
 */
HASDK_API int HASDK_CALL HA_AppReboot(HA_Cam* cam);

/**
*  @brief 人员信息同步接口，支持对人员的添加、修改、删除
*  @param  [IN] cam 要注册的相机句柄
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] imgs 人脸图像，图像格式须为JPG
*  @param  [IN] img_count 图像数量
*  @param  [IN] picture_flags 下发图像到相机的标识，0表示不存图片到相机, >0 表示存到相机的图片数量
*  @param  [IN] syncFlag 同步模式标识，  //HA_FACE_ADD:添加人员信息, HA_FACE_UPDATE:修改人员信息, HA_FACE_DEL:删除人员信息
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_FaceSyncInterface(HA_Cam* cam, struct FaceFlags *faceID, struct FaceImage *imgs, int img_count, int picture_flags, int syncFlag);

/**
*  @brief 注册人脸到相机，支持单个id多张人脸 最大5张人脸图像
*  @param  [IN] cam 要注册的相机句柄
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] jpg 人脸图像路径数组，图像格式须为JPG
*  @param  [IN] img_count 图像路径数量
*  @param  [IN] picture_flags 下发图像到相机的标识，0表示不存图片到相机, >0 表示存到相机的图片数量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_AddJpgPaths(HA_Cam* cam, struct FaceFlags *faceID, char *jpg[], int img_count, int picture_Flags);

/**
*  @brief 注册人脸到相机，支持单个id多张人脸 最大5张人脸图像
	注：与HA_AddJpgPaths效果相同 现只维护HA_AddJpgPaths  此接口废弃
*  @param  [IN] cam 要注册的相机句柄
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] jpg 人脸图像路径数组，图像格式须为bmp
*  @param  [IN] img_count 图像路径数量
*  @param  [IN] picture_flags 下发图像到相机的标识，0表示不存图片到相机, >0 表示存到相机的图片数量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_AddImagePaths(HA_Cam* cam, struct FaceFlags *faceID, char *jpg[], int img_count, int picture_flags);

/**
*  @brief 注册人脸到相机，支持单个id多张人脸
*  @param  [IN] cam 要注册的相机句柄
*  @param  [IN] type 注册类型， 0表示添加 1表示修改
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] jpg 人脸图像路径数组
*  @param  [IN] img_count 图像数量
*  @param  [IN] picture_flags 下发图像到相机的标识，0表示不存图片到相机, >0 表示存到相机的图片数量
*  @param  [OUT] err_imgs 注册失败的人脸图像，图片编号对应imgs下的图片编号
*  @param  [OUT] err_imgs_count 注册失败的人脸图像数量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_JpgPathsEx(HA_Cam* cam, int type, struct FaceFlags *faceID, char *jpg[], int img_count, int picture_Flags, struct ErrorFaceImage *err_imgs, int *err_imgs_count);

/**
*  @brief 注册人脸到相机，支持单个id多张人脸 最大5张人脸图像
*  @param  [IN] cam 要注册的相机句柄
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] imgs 人脸图像
*  @param  [IN] img_count 图像数量
*  @param  [IN] picture_flags 下发图像到相机的标识，0表示不存图片到相机, >0 表示存到相机的图片数量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_AddJpgFaces(HA_Cam* cam, struct FaceFlags *faceID, struct FaceImage *imgs, int img_count, int picture_flags);

/**
*  @brief 注册人脸到相机，支持单个id多张人脸 最大5张人脸图像
*  @param  [IN] cam 要注册的相机句柄
*  @param  [IN] type 注册类型， 0表示添加 1表示修改
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] imgs 人脸图像，图像格式须为JPG
*  @param  [IN] img_count 图像数量
*  @param  [IN] picture_flags 下发图像到相机的标识，0表示不存图片到相机, >0 表示存到相机的图片数量
*  @param  [OUT] err_imgs 注册失败的人脸图像，图片编号对应imgs下的图片编号
*  @param  [OUT] err_imgs_count 注册失败的人脸图像数量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_JpgFacesEx(HA_Cam* cam, int type, struct FaceFlags *faceID, struct FaceImage *imgs, int img_count, int picture_flags, struct ErrorFaceImage *err_imgs, int *err_imgs_count);

/**
*  @brief 注册人脸到相机，注册图像尺寸要求大于100*100，注册人脸尺寸大于80*80
	注：此接口已被HA_AddJpgFaces 替代不再维护  (现保留只为低版本做兼容 写于2018-12-13)
*  @param  [IN] cam 要注册的相机句柄
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] jpg 人脸图像，图像格式须为JPG
*  @param  [IN] len jpg数据长度
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_AddJpgFace(HA_Cam* cam, struct FaceFlags *faceID, const unsigned char *jpg, int len);

/**
*  @brief 注册人脸到相机，支持单个id多张人脸 最大5张人脸图像
*  @param  [IN] cam 要注册的相机句柄
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] imgs 人脸图像 图片数据必须为BRG
*  @param  [IN] img_count 图像数量
*  @param  [IN] picture_flags 下发图像到相机的标识，0表示不存图片到相机, >0 表示存到相机的图片数量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_AddFaces(HA_Cam* cam, struct FaceFlags *faceID, struct FaceImage *imgs, int img_count, int picture_flags);

/**
*  @brief 注册人脸到相机，支持单个id多张人脸 最大5张人脸图像
*  @param  [IN] cam 要注册的相机句柄
*  @param  [IN] type 注册类型， 0表示添加 1表示修改
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] imgs 人脸图像，图片数据必须为BRG
*  @param  [IN] img_count 图像数量
*  @param  [IN] picture_flags 下发图像到相机的标识，0表示不存图片到相机, >0 表示存到相机的图片数量
*  @param  [OUT] err_imgs 注册失败的人脸图像，图片编号对应imgs下的图片编号
*  @param  [OUT] err_imgs_count 注册失败的人脸图像数量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_FacesEx(HA_Cam* cam, int type, struct FaceFlags *faceID, struct FaceImage *imgs, int img_count, int picture_flags, struct ErrorFaceImage *err_imgs, int *err_imgs_count);

/**
*  @brief 注册人脸到相机，注册图像尺寸要求大于100*100，注册人脸尺寸大于80*80
	注：此接口已被HA_AddFaces 替代不再维护 (现保留只为低版本做兼容  写于2018-12-13)
*  @param  [IN] cam cam 要注册的相机句柄
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] rgbimage 人脸图像，图像格式须为RGB24
*  @param  [IN] width 人脸图像宽度
*  @param  [IN] height 人脸图像高度
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_AddFace(HA_Cam* cam, struct FaceFlags *faceID, const unsigned char *rgbimage, int width, int height);

/**
*  @brief 注册人脸特征，或者人脸姓名
*  @param  [IN] cam 相机句柄
*  @param  [IN] faceID 要注册的人脸ID
*  @param  [IN] features 特征数据，按[特征值1]...[特征值n]排列
*  @param  [IN] features_size 单个特征数据大小
*  @param  [IN] features_num 特征数据数量
*  @param  [IN] imgs 下发到相机的人脸图片
*  @param  [IN]  img_num 是否下发缩略图 ：0 不下发 1：下发
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_AddFacePacket(HA_Cam* cam, struct FaceFlags *faceID, float *features, int features_size, int features_num, struct FaceImage *imgs, int img_num);

/**
*  @brief  相机同步注册 
*  @param  [IN] cam 要修改的相机句柄
*  @param  [IN] faceID 要注册的人脸ID
*  @param  [IN] feature 特征数据 填NULL为不添加特征数据
*  @param  [IN] twist_img 归一化图像   (必须)
*  @param  [IN] twist_num 归一化图像数量
*  @param  [IN] imgs 下发到相机的人脸图片  
*  @param  [IN] img_num 是否下发缩略图 ：0 不下发 1：下发
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_FacePacketSync(HA_Cam* cam, struct FaceFlags *faceID, struct FaceFeature* feature, struct FaceImage* twist_imgs, int twist_num, struct FaceImage *imgs, int img_num);

/**
*  @brief 注册人脸特征，或者人脸姓名 
*  @param  [IN] cam 要修改的相机句柄
*  @param  [IN] type 注册类型， 0表示添加 1表示修改
*  @param  [IN] faceID 要注册的人脸ID
*  @param  [IN] features 特征数据，按[特征值1]...[特征值n]排列
*  @param  [IN] features_size 单个特征数据大小
*  @param  [IN] features_num 特征数据数量
*  @param  [IN] imgs 下发到相机的人脸图片
*  @param  [IN] img_num 下发到相机的人脸图片数量
*  @param  [OUT] err_imgs 注册失败的人脸图像，图片编号对应imgs下的图片编号
*  @param  [OUT] err_imgs_count 注册失败的人脸图像数量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_FacePacketEx(HA_Cam* cam, int type, struct FaceFlags *faceID, float *features, int features_size, int features_num, struct FaceImage *imgs, int img_num, struct ErrorFaceImage *err_imgs, int *err_imgs_count);

/**
*  @brief 修改人脸信息，支持单个id多张人脸 最大5张人脸图像
*  @param  [IN] cam 要修改的相机句柄
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] jpg 人脸图像路径数组，图像格式须为JPG
*  @param  [IN] img_count 图像路径数量
*  @param  [IN] picture_flags 下发图像到相机的标识，0表示不存图片到相机, >0 表示存到相机的图片数量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_ModifyJpgPaths(HA_Cam* cam, struct FaceFlags *faceID, char *jpg[], int img_count, int picture_Flags);
/**
* 废弃
*/
HASDK_API int HASDK_CALL HA_ModifyImagePaths(HA_Cam* cam, struct FaceFlags *faceID, char *jpg[], int img_count, int picture_flags);

/**
*  @brief 修改人脸信息，支持单个id多张人脸 最大5张人脸图像
*  @param  [IN] cam 要修改的相机句柄
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] imgs 人脸图像，图像格式须为JPG
*  @param  [IN] img_count 图像数量
*  @param  [IN] picture_flags 下发图像到相机的标识，0表示不存图片到相机, >0 表示存到相机的图片数量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_ModifyJpgFaces(HA_Cam* cam, struct FaceFlags *faceID, struct FaceImage *imgs, int img_count, int picture_flags);

/**
*   废弃
*/
HASDK_API int HASDK_CALL HA_ModifyJpgFace(HA_Cam* cam, struct FaceFlags *faceID, const unsigned char *jpg, int len);

/**
*  @brief 修改人脸信息，支持单个id多张人脸 最大5张人脸图像
*  @param  [IN] cam 要修改的相机句柄
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] imgs 人脸图像，图像格式须为RGB数据
*  @param  [IN] img_count 图像数量
*  @param  [IN] picture_flags 下发图像到相机的标识，0表示不存图片到相机, >0 表示存到相机的图片数量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_ModifyFaces(HA_Cam* cam, struct FaceFlags *faceID, struct FaceImage *imgs, int img_count, int picture_flags);

/**
*  
*  废弃
*/
HASDK_API int HASDK_CALL HA_ModifyFace(HA_Cam* cam, struct FaceFlags *faceID, const unsigned char *rgbimage, int width, int height);

/**
*  @brief 修改人脸特征，或者人脸姓名
*  @param  [IN] cam 要修改的相机句柄
*  @param  [IN] faceID 要修改的人脸ID
*  @param  [IN] features 特征数据，按[特征值1]...[特征值n]排列
*  @param  [IN] features_size 单个特征数据大小
*  @param  [IN] features_num 特征数据数量
*  @param  [IN] imgs 下发到相机的人脸图片
*  @param  [IN] img_num 下发到相机的人脸图片数量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_ModifyFacePacket(HA_Cam* cam, struct FaceFlags *faceID, float *features, int features_size, int features_num,struct FaceImage *imgs, int img_num);


/**
*  @brief  jpg图片直接注册人脸信息，支持单个id多张人脸 现仅支持1张人脸图像 最大尺寸不超过1920 容量不超过3M
*  @param  [IN] cam 要修改的相机句柄
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] imgs 人脸图像，图像格式须为jpg数据
*  @param  [IN] img_count 图像数量 = 1
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_AddFacesByJpg(HA_Cam* cam, struct FaceFlags *faceID, struct FaceImage *imgs, int img_count);

/**
*  @brief  jpg图片直接修改人脸信息，支持单个id多张人脸 现仅支持1张人脸图像 最大尺寸不超过1920 容量不超过3M
*  @param  [IN] cam 要修改的相机句柄
*  @param  [IN] faceID 人员标记，用于唯一标记注册的人脸
*  @param  [IN] imgs 人脸图像，图像格式须为jpg数据
*  @param  [IN] img_count 图像数量 = 1 
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_ModifyFacesByJpg(HA_Cam* cam, struct FaceFlags *faceID, struct FaceImage *imgs, int img_count);

/**
*  @brief 删除一个人员信息
*  @param  [IN] cam 要注销的相机句柄
*  @param  [IN] personID  需要删除的人脸ID
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_DeleteFaceDataByPersonID(HA_Cam* cam,const char* personID);

/**
*  @brief 按角色删除
*  @param  [IN] cam 要注销的相机句柄
*  @param  [IN] role  需要删除的人脸角色  0：删除所有普通人员 1：删除所有白名单人员 2：删除所有黑名单人员 3：删除所有人员记录
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_DeleteFaceDataByPersonRole(HA_Cam* cam, int role);


/**
*  @brief 删除所有人脸
*  @param  [IN] cam 要删除的相机句柄
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_DeleteFaceDataAll(HA_Cam* cam);

/**
*  @brief 获取已经添加的人脸中总数 注：会触发注册查询回调函数
*  @param  [IN] cam 相机句柄
*  @return 返回已经添加的人脸总数，返回值小于0表示出错，参考错误码
*/
HASDK_API int HASDK_CALL HA_GetFaceIDTotal(HA_Cam* cam);


/**
*  @brief  人脸库容量查询
*  @param  [IN] cam 要查看的相机句柄
*  @param  [OUT] infor 人脸库容量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_StorageCapacity(HA_Cam* cam,struct StorageCapacity* infor);


/**
*  @brief 通过人员记录编号查询 (废弃 此接口不再更新)
*  @param  [IN] cam 要查看的相机句柄
*  @param  [OUT] result 人员信息 
*  @param  [IN] record_no 查询第几条数据,从1开始
*  @param  [IN] featureFlags 特征查询标记，是否查询特征信息，0表示不需要，非0表示需要
*  @param  [IN] imgFlags 是否查询人脸图像  
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_QueryFaceID(HA_Cam* cam,struct QueryFaceFlags *result, int record_no, char featureFlags, char imgFlags);

/**
*  @brief 通过人员角色查询
*  @param  [IN] cam 要查看的相机句柄
*  @param  [IN] role 要查询的人员角色 0：普通人员。 1：白名单人员。 2：黑名单人员。 -1：所有人员。
*  @param  [IN] page_no 要查询的页码
*  @param  [IN] page_size 每页的数据条数，用于数据分页 最大值100
*  @param  [IN] featureFlags 特征查询标记，是否查询特征信息，0表示不需要，非0表示需要
*  @param  [IN] imgFlags 是否查询人脸图像
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_QueryByRole(HA_Cam* cam, int role, int page_no, int page_size, char featureFlags, char imgFlags);

/**
*  @brief 人员查询扩展，支持按条件查询，以及模糊查询
*  @param  [IN] cam 要查看的相机句柄
*  @param  [IN] role 要查询的人员角色 0：普通人员。 1：白名单人员。 2：黑名单人员。 -1：所有人员。
*  @param  [IN] page_no 要查询的页码
*  @param  [IN] page_size 每页的数据条数，用于数据分页 最大值100
*  @param  [IN] featureFlags 特征查询标记，是否查询特征信息，0表示不需要，非0表示需要
*  @param  [IN] imgFlags 是否查询特征信息，0表示不需要，非0表示需要
*  @param  [IN] condition_flag 用于标记按哪些条件查询，使用enum ConditionFlag来控制，0：无效，非0：有效
*  @param  [IN] query_mode 0表示精确查询，非0表示模糊查询
*  @param  [IN] condition 查询条件
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_QueryFaceEx(HA_Cam* cam, int role, int page_no, int page_size, char featureFlags, char imgFlags, short condition_flag, short query_mode, struct QueryCondition *condition);


/**
*  @brief  历史记录容量查询
*  @param  [IN] cam 要查看的相机句柄
*  @param  [OUT] infor 抓拍记录容量
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_QueryCapacityHistory(HA_Cam* cam, struct CapacityHistory* infor);


/**
*  @brief 历史记录查询
*  @param  [IN] cam 要查看的相机句柄
*  @param  [IN] page_no 要查询的页码
*  @param  [IN] page_size 每页的数据条数，用于数据分页 最大值100
*  @param  [IN] condition 查询条件
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_QueryFaceRecord(HA_Cam* cam, int page_no, int page_size, struct RecordCondition *condition);

/**
*  @brief 通过序列号删除历史记录
*  @param  [IN] cam 要删除的相机句柄
*  @param  [IN] sequence 删除纪录的序列号
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_DeleteFaceRecordBySequence(HA_Cam* cam, unsigned int sequence);

/**
*  @brief 清除历史记录
*  @param  [IN] cam 要清除的相机句柄
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_DeleteFaceRecordAll(HA_Cam* cam);


/**
* 预留
*/
HASDK_API int HASDK_CALL HA_QueryMntRecord(HA_Cam* cam, char* data, int* dataSize, struct ImageInfo* infor);

/**
*  @brief 废弃
*/
HASDK_API int HASDK_CALL HA_GetJpgFaceFeature(const unsigned char *jpg, int len, float *feature, int *feature_size);

/**
*  @brief 获取两个特征值的匹配分数
*  @param  [IN] f1 特征值1
*  @param  [IN] f2 特征值2
*  @param  [IN] feature_size 特征值大小
*  @return 返回值为相似度分数（0~100）
*/
HASDK_API int HASDK_CALL HA_GetMatchScores(const float* f1, const float* f2, int feature_size);

/**
*  废弃
*/
HASDK_API int HASDK_CALL HA_GetJpgFaceRectAndFeature(const unsigned char *jpg, int len, float *feature, int *feature_size, struct ha_rect *faceRect, unsigned char *faceImgJpg, int *faceJpgLen);

/**
*  废弃
*/
HASDK_API int HASDK_CALL HA_GetJpgPathRectAndFeature(const unsigned char *img_path, float *feature, int *feature_size, struct ha_rect *faceRect, unsigned char *faceImgJpg, int *faceJpgLen);

/**
*  废弃
*/
HASDK_API int HASDK_CALL HA_GetFaceRectAndFeature( const unsigned char *rgbimage, int width, int height, float *feature, int *feature_size, struct ha_rect *faceRect, unsigned char *faceImgJpg, int *faceJpgLen);

/**
*  @brief 提取归一化图像
*  @param  [IN] img_path 人脸图像文件路径
*  @param  [OUT] twist_image 归一化图像数据 bgr格式 至少分配70K内存
*  @param  [OUT] twist_size 归一化图像数据长度
*  @param  [OUT] twist_width 归一化图像数化宽
*  @param  [OUT] twist_height 归一图像高
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_GetJpgPathTwist(const unsigned char *img_path, unsigned char *twist_image, int *twist_size, int *twist_width, int *twist_height);

/**
*  @brief 提取归一化图像
*  @param  [IN] jpg 人脸图像，图像格式须为JPG
*  @param  [IN] len jpg数据长度
*  @param  [OUT] twist_image 归一化图像数据 bgr格式 至少分配70K内存
*  @param  [OUT] twist_size 归一化图像数据长度
*  @param  [OUT] twist_width 归一化图像数宽
*  @param  [OUT] twist_height 归一化图像高
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_GetJpgFaceTwist(const unsigned char *jpg, int len, unsigned char *twist_image, int *twist_size, int *twist_width, int *twist_height);

/**
*  @brief 提取归一化图像
*  @param  [IN] bgrimage 人脸图像，图像格式须为bgr
*  @param  [IN] width 人脸图像宽度
*  @param  [IN] height 人脸图像高度
*  @param  [OUT] twist_image 归一化图像数据 bgr格式 至少分配70K内存
*  @param  [OUT] twist_size 归一化图像数据长度
*  @param  [OUT] twist_width 归一化图像数宽
*  @param  [OUT] twist_height 归一化图像高
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_GetFaceTwist( const unsigned char *bgrimage, int width, int height, unsigned char *twist_image, int *twist_size, int *twist_width, int *twist_height);

/**
*  @brief 人脸检测接口
*  @param  [IN] bgrimage 人脸图像，图像格式须为bgr
*  @param  [IN] width 人脸图像宽度
*  @param  [IN] height 人脸图像高度
*  @param  [OUT] rect 人脸矩形区域坐标
*  @param  [OUT] oripoint 5个点坐标，须分配5个Point的内存
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_FaceDetect( const unsigned char *rgbimage, int width, int height,  struct ha_rect *rect, struct HA_Point *oripoint);

/**
*  @brief 提取归一化图像和人脸略缩图像
*  @param  [IN] bgrimage 人脸图像，图像格式须为bgr
*  @param  [IN] width 人脸图像宽度
*  @param  [IN] height 人脸图像高度
*  @param  [OUT] twist_image 归一化图像数据 bgr格式 至少分配70K内存
*  @param  [OUT] twist_size 归一化图像数据长度
*  @param  [OUT] twist_width 归一化图像数宽
*  @param  [OUT] twist_height 归一化图像高
*  @param  [OUT] faceImgJpg 抠出的人脸略缩图像
*  @param  [OUT] faceJpgLen 抠出的人脸略缩图像长度
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_GetFeatureImage(const unsigned char *bgrimage, int width, int height, unsigned char *twist_image, int *twist_size, int *twist_width, int *twist_height,unsigned char *faceImgJpg, int *faceJpgLen);

/**
*  @brief 提取归一化图像和人脸略缩图像
*  @param  [IN] jpg 人脸图像，图像格式须为JPG
*  @param  [IN] len jpg数据长度
*  @param  [OUT] twist_image 归一化图像数据 bgr格式 至少分配70K内存
*  @param  [OUT] twist_size 归一化图像数据长度
*  @param  [OUT] twist_width 归一化图像数宽
*  @param  [OUT] twist_height 归一化图像高
*  @param  [OUT] faceImgJpg 抠出的人脸略缩图像
*  @param  [OUT] faceJpgLen 抠出的人脸略缩图像长度
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_GetJpgFeatureImage(const unsigned char *jpg, int len,unsigned char *twist_image, int *twist_size, int *twist_width, int *twist_height, unsigned char *faceImgJpg, int *faceJpgLen);

/**
*  @brief  通过路径提取归一化图像和人脸略缩图像
*  @param  [IN] jpg 人脸图像路径，图像格式须为JPG
*  @param  [OUT] twist_image 归一化图像数据 bgr格式 至少分配70K内存
*  @param  [OUT] twist_size 归一化图像数据长度
*  @param  [OUT] twist_width 归一化图像数宽
*  @param  [OUT] twist_height 归一化图像高
*  @param  [OUT] faceImgJpg 抠出的人脸略缩图像
*  @param  [OUT] faceJpgLen 抠出的人脸略缩图像长度
*  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
*/
HASDK_API int HASDK_CALL HA_GetJpgPathFeatureImage(const unsigned char *img_path, unsigned char *twist_image, int *twist_size, int *twist_width, int *twist_height, unsigned char *faceImgJpg, int *faceJpgLen);

/**
*  @brief 检测图片是否符合注册条件
*  @param  [IN] jpg 人脸图像，图像格式须为JPG
*  @param  [IN] len jpg数据长度
*  @return 返回值为0表示可注册，返回负数表示不适合注册，具体参考错误码
*/
HASDK_API int HA_FaceJpgLegal(const unsigned char *jpg, int len);

/**
 * 废弃
 */
HASDK_API void HASDK_CALL HA_RegServerConnectCb(HA_ServerConnectCb_t cb,void* userParam);

/**
*  废弃 
*/
HASDK_API void HASDK_CALL HA_InitServer(int port,int port_FaceReco,int*errNum);

/**
*  废弃
*/
HASDK_API void HASDK_CALL HA_DeInitServer();

/**
* @brief   通过中转服务搜索相机搜索相机
* @param   offset [in] 从第几页开始 
* @param   page_num 搜索多少条[in] 
* @return  无                       
*/ 
HASDK_API int HASDK_CALL HA_SearchCam(HA_Cam* cam,int offset, int page_num);

/**
* @brief   通过中转服务搜索相机搜索相机拓展
* @param   offset [in] 从第几页开始 
* @param   page_num 搜索多少条[in] 
* @param   camid 序列号[in] 
* @param   posname 点位名称[in] 
* @param   posid 点位ID[in] 
* @return  无                       
*/ 
HASDK_API int HASDK_CALL HA_SearchCamEx(HA_Cam* cam,int offset, int page_num,const char* camid ,const char* posname,const char* posid);

/**
* @brief   注册服务器搜索相机回调函数
* @param   cam 句柄
* @param   cb[in] 回调函数指针
* @param   usrParam[in] 用户参数
* @return  无                       
*/ 
HASDK_API void HASDK_CALL HA_RegSearchCamCb(HA_Cam* cam, HA_SearchCamCb_t cb, void* usrParam);

/**
* @brief   通过服务器映射到相机
* @param   cam 句柄
* @param   devId[in]  要映射的相机设备序列号
* @param   resv[in]   保留
* @return  无                       
*/ 
HASDK_API int HASDK_CALL HA_MapToCam(HA_Cam* cam,const char * devId, const char* resv);

/**
* @brief   中转服务器 是否接收人脸抓拍数据
* @param   cam 句柄
* @param   flag[in]  0:否 !0:是
* @return  无                       
*/ 
HASDK_API int HASDK_CALL HA_FaceRecoInfoCtl(struct HA_Cam* cam, int flag);

/**
 * @brief   连接相机到服务器 
 * @param   ip[in]   服务器ip
 * @param   port[in]   服务器端口
 * @param   usrName[in]   保留
 * @param   password[in]  保留
 * @param   errorNum[out]  连接失败错误号，0为连接成功，-1为连接失败
 * @return  NULL 连接失败
 * @return  非NULL 连接成功  
 */
HASDK_API HA_Cam* HASDK_CALL HA_ConnectRelayServer(const char* ip, unsigned short port, const char* usrName, const char* password, int* errorNum);

/**
 * @brief   发送json命令到相机
 * @param   cam[in]  相机句柄
 * @param   cmd[in]  json cmd字段
 * @param   json[in] json 数据
 * @param   jsonSize[in]  json 数据长度 最长不超过 8M
 * @param   replyJson[out]  回复内容
 * @param   buffSize[in]  replyJson Buff长度
 * @return  0 发送成功              
 * @return  <0 发送失败  参考错误码 
 */
HASDK_API int HASDK_CALL HA_SendJson(struct HA_Cam* cam, const char* cmd, const char* json, unsigned int jsonSize, char* replyJson ,int buffSize);

/**
 * @brief   设置中转服务器地址 
 * @param   ip[in]   服务器ip
 * @param   UpdataServerParam[in]   服务器参数 注：URL不填
 * @return  0 设置成功              
 * @return  <0 设置失败  参考错误码 
 */
HASDK_API int HASDK_CALL HA_SetRelayServerParam(struct HA_Cam* cam,const struct UpdataServerParam* param);
    
HASDK_API void HASDK_CALL HA_TestDLL(void* test);

#ifdef __cplusplus
}
#endif

#endif


