
#include "Proto_NZ.h"
#include "HASdkDef.h"

using namespace std;


int QUERY_DELETE_FACE(uint8_t* send_pb, int* pbLength, int controll)
{
	OperationFaceId opertion = OperationFaceId_init_zero;

	sprintf(opertion.faceId, "%s_%d", "test_id", 1);
	sprintf(opertion.dev.dev, "%s", "wuhuaixi123");
	opertion.operation = controll;
	//sprintf(mAddFcae.face.userParam, "%s", "age=5;sex=1");

	pb_ostream_t stream = pb_ostream_from_buffer(send_pb, *pbLength);
	pb_encode_tag(&stream, PB_WT_VARINT, MsgType_OperationFaceId_tag);
	bool status = pb_encode(&stream, OperationFaceId_fields, &opertion);
	if (!status)
	{
		printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
		return -1;
	}
	//pb = send_pb;
	*pbLength = (int)stream.bytes_written;
	return 1;
}
int QUERY_DELETE_FACE_REQ(pb_istream_t* istream,char* faceId,int* operation)
{
	OperationFaceId opertion = OperationFaceId_init_zero;
	bool decode_status;
	decode_status = pb_decode(istream, OperationFaceId_fields, &opertion);
	if (!decode_status)
	{
		printf("pb_decode failed: %s\n", PB_GET_ERROR(istream));
		return -1;
	}
	sprintf(faceId, "%s", opertion.faceId);
	*operation = opertion.operation;
	return 1;
	//printf("ddddd==%s\n", opertion.faceId);
	//printf("ddddd==%d\n", opertion.operation);
	//printf("ddddd==%d\n", face.face.effectTime);
}
int HA_ADD_FACE_REQ(pb_istream_t* istream)
{
	AddFcae face = AddFcae_init_zero;
	bool decode_status;
	decode_status = pb_decode(istream, AddFcae_fields, &face);
	if (!decode_status)
	{
		printf("pb_decode failed: %s\n", PB_GET_ERROR(istream));
		return -1;
	}
	printf("ddddd==%d\n", face.face.effectStartTime);
	printf("ddddd==%s\n", face.face.faceID);
	printf("ddddd==%d\n", face.face.effectTime);
	return 1;
}
int HA_ADD_FACE(uint8_t* send_pb, int* pbLength)
{
	AddFcae mAddFcae = AddFcae_init_zero;
	sprintf(mAddFcae.face.faceID, "%s_%d", "test_id", 1);
	sprintf(mAddFcae.face.faceName, "%s", "天涯");
	//sprintf(mAddFcae.face.userParam, "%s", "age=5;sex=1");
	mAddFcae.face.effectStartTime = 100000;
	mAddFcae.face.effectTime = 0xFFFFFFFF;
	mAddFcae.face.role = 2;
	mAddFcae.face.wgCardNO = 10;

	sprintf(mAddFcae.picture.jpgName, "%s", "abc");
	sprintf(mAddFcae.picture.libName, "%s", "abc");
	mAddFcae.picture.jpgLengt = 58222;
	mAddFcae.picture.picId = 1234;
	mAddFcae.picture.libId = 888936;

	pb_ostream_t stream = pb_ostream_from_buffer(send_pb, *pbLength);
	pb_encode_tag(&stream, PB_WT_VARINT, MsgType_AddFcae_tag);
	bool status = pb_encode(&stream, AddFcae_fields, &mAddFcae);
	if (!status)
	{
		printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
		return -1;
	}
	//pb = send_pb;
	*pbLength = (int)stream.bytes_written;
	return 1;
}
void ErrorCheck(int error)
{
	//printf("ErrorCheck \n");
	if (error != 0)
	{
		//printf("ErrorCheck if (error!= 0)\n");
		switch (error)
		{
		case ERR_NONE://                    0    //无错误
			printf("Error------ERR_NONE \n");
			break;
		case ERR_INVALID_PARAM: //://- 1   //不合法的值
			printf("Error------ERR_INVALID_PARAM \n");
			break;
		case ERR_TIMEOUT://- 2   //响应超时
			printf("Error------ERR_TIMEOUT \n");
			break;
		case ERR_SEND_BUF_FULL://- 3   //发送缓存已满
			printf("Error------ERR_SEND_BUF_FULL \n");
			break;
		case ERR_SYS_NOT_MATCH://- 4   //保留
			printf("Error------ERR_SYS_NOT_MATCH \n");
			break;
		case ERR_UNCONNECTED://- 5   //相机未连接
			printf("Error------ERR_UNCONNECTED \n");
			break;
		case ERR_SNAPSHOT_UNAVAILABLE://- 6   //截图失败
			printf("Error------ERR_SNAPSHOT_UNAVAILABLE \n");
			break;
		case ERR_JPEG_ENCODE_ERROR://- 7   //JPEG解码失败
			printf("Error------JPEGERR_JPEG_ENCODE_ERROR \n");
			break;
		case ERR_BUF_TOO_SMALL://- 8   //缓存空间不足
			printf("Error------ERR_BUF_TOO_SMALL \n");
			break;
		case ERR_CANCEL://- 9   //保留
			printf("Error------ERR_CANCEL \n");
			break;
		case ERR_UNABLE_TO_OPEN_FILE:    //- 10  //文件打开失败
			printf("Error------ERR_UNABLE_TO_OPEN_FILE \n");
			break;
		case ERR_DEVICE_NOT_SUPPORTED://- 11  //设备不支持
			printf("Error------ERR_DEVICE_NOT_SUPPORTED \n");
			break;
		case ERR_COUNT_INVALID://- 12  //保留
			printf("Error------ERR_COUNT_INVALID \n");
			break;
		case ERR_OUT_PUT_OF_ARRAY://- 13  //保留
			printf("Error------ERR_OUT_PUT_OF_ARRAY \n");
			break;
		case ERR_GET_FACE_FEATURE://- 14   //提取人脸特征失败，须保证图像中有且仅有一张人脸
			printf("Error------ERR_GET_FACE_FEATURE \n");
			break;
		case ERR_FACE_ID_REPEAT://- 15   //添加人员失败，人员id重复
			printf("Error------ERR_FACE_ID_REPEAT \n");
			break;
		case ERR_FACE_ID_NOT_EXITS://- 16   //修改人脸特征失败，未找到对应ID
			printf("Error------ERR_FACE_ID_NOT_EXITS \n");
			break;
		case ERR_GET_FACE_INIT://- 17   //人脸提取器未初始化，请调用HA_InitFaceModel初始化
			printf("Error------ERR_GET_FACE_INIT \n");
			break;
		case ERR_GET_FACE_ID://- 18   //无当前记录
			printf("Error------ERR_GET_FACE_ID \n");
			break;
		case ERR_SERIAL_INDEX://- 19   //错误的串口编号，目前只支持HA_SERIAL_RS485和HA_SERIAL_RS232
			printf("Error------ERR_SERIAL_INDEX \n");
			break;
		case ERR_SYSTEM_REBOOT://- 20   //重启系统失败
			printf("Error------ERR_SYSTEM_REBOOT \n");
			break;
		case ERR_APP_REBOOT://- 21   //重启应用程序失败
			printf("Error------ERR_APP_REBOOT \n");
			break;
		case ERR_ENCODE_JPG://- 22   //压缩图像失败
			printf("Error------ERR_ENCODE_JPG \n");
			break;
		case ERR_FACES_NUM://- 23   //单个人员最大支持5张图像
			printf("Error------ERR_FACES_NUM \n");
			break;
		case ERR_IMAGE_DECODE://- 24   //图像解码失败
			printf("Error------ERR_IMAGE_DECODE \n");
			break;
		case ERR_IMAGE_SIZE://- 25   //图像太大，用于提取特征的jpg图像不能超过10M，jpg 直接注册图像不超过6M 
			printf("Error------ERR_IMAGE_SIZE  \n");
			break;
		case ERR_IMAGE_PATH://- 26   //文件不存在，请检查图片路径是否正确
			printf("Error------ERR_IMAGE_PATH\n");
			break;
		case ERR_SAVE_IMG_NUM://- 27   //目前相机只支持存一张模板图像，pictureFlags必须<=1
			printf("Error------ERR_SAVE_IMG_NUM\n");
			break;
		case ERR_PTZ_CTRL://- 28   //不支持的云台控制，目前只支持5：变倍（放大） 6：变倍（缩小） 7：聚焦（拉近） 8：聚焦（拉远）
			printf("Error------ERR_PTZ_CTRL\n");
			break;
		case ERR_PTZ_CTRL_MODE://- 29   //不支持的控制模式，1：一次运动 2：启动 3：停止
			printf("Error------ERR_PTZ_CTRL_MODE \n");
			break;
		case ERR_DAEMON_REQUEST://- 30   //保留
			printf("Error------ERR_DAEMON_REQUEST \n");
			break;
		case ERR_UPPER_LIMIT://- 31   //人员数量已达上限
			printf("Error------ERR_UPPER_LIMIT \n");
			break;
		case ERR_PROTOCAL_VER://- 32   //协议版本不匹配，请确认SDK和相机固件版本
			printf("Error------ERR_PROTOCAL_VER\n");
			break;
		case ERR_REQUEST_CMD://- 33   //不支持的操作请求
			printf("Error------ERR_REQUEST_CMD \n");
			break;
		case ERR_PACKET_DATA://- 34   //请求数据包包含不合法字段
			printf("Error------ERR_PACKET_DATA \n");
			break;
		case ERR_AUTH_FAILED://- 35   //认证失败
			printf("Error------ERR_AUTH_FAILED \n");
			break;
		case ERR_WRITE_DATA://- 36   //写入数据失败
			printf("Error------ERR_WRITE_DATA \n");
			break;
		case ERR_READ_DATA://- 37   //读取数据失败
			printf("Error------ERR_READ_DATA \n");
			break;
		case ERR_TWIST_FACE://- 38   //归一化图像失败
			printf("Error------ERR_TWIST_FACE \n");
			break;
		case ERR_EXTRACT_FEATURE://- 39   //提取特征失败
			printf("Error------ERR_EXTRACT_FEATURE \n");
			break;
		case ERR_MIN_FACE://- 40   //人脸尺寸太小，人脸轮廓必须大于96*96
			printf("Error------ERR_MIN_FACE \n");
			break;
		case ERR_QVALUE_TOO_SMALL://- 41   //人像质量太差不满足注册条件
			printf("Error------ERR_QVALUE_TOO_SMALL \n");
			break;
		case ERR_INVALID_SYNC_MODE://- 42   //无效的同步操作
			printf("Error------ERR_INVALID_SYNC_MODE \n");
			break;
		case ERR_WG_QUERY_MODE://- 43   //韦根卡号不支持模糊查询
			printf("Error------ERR_WG_QUERY_MODE\n");
			break;
		case ERR_SYSTEM_BUSY://- 44   //操作系统繁忙
			printf("Error------ERR_SYSTEM_BUSY\n");
			break;
		case ERR_VERSION_MATCH://- 45   //版本不匹配
			printf("Error------ERR_VERSION_MATCH\n");
			break;
		case ERR_TOO_MUCH_FACE://- 46   //图像中人脸数不为1
			printf("Error------ERR_TOO_MUCH_FACE \n");
			break;
		case ERR_FACE_INCOMPLETE://- 47     //图像中人脸不完整
			printf("Error------ERR_FACE_INCOMPLETE \n");
			break;
		case ERR_ANGLE_PITCH://- 48     //人脸俯仰角太大
			printf("Error------ERR_ANGLE_PITCH \n");
			break;
		case ERR_ANGLE_YAW://- 49     //人脸侧偏角太大
			printf("Error------ERR_ANGLE_YAW \n");
			break;
		case ERR_ANGLE_ROLL://- 50     //人脸不正
			printf("Error------ERR_ANGLE_ROLL \n");
			break;
		case ERR_MOUTH_OPEN://- 51     //张嘴幅度过大
			printf("Error------ERR_MOUTH_OPEN \n");
			break;
		case ERR_YINYANG_FACE://- 52     //光照不均匀
			printf("Error------ERR_YINYANG_FACE \n");
			break;
		case ERR_VISIBLE_TARGET://- 54    // 未检出指定个数可见光目标*/
			printf("Error------ERR_VISIBLE_TARGET \n");
			break;
		case ERR_INFRARED_TARGET://- 55    //未检出指定个数红外光目标*/
			printf("Error------ERR_INFRARED_TARGET \n");
			break;
		case ERR_ABERRATION_TOO_BIG://- 56     // 可见光红外光像差过大*/
			printf("Error------ERR_ABERRATION_TOO_BIG \n");
			break;
		case ERR_REPLYCODE_FEATURE_VERSION://- 60  //特征数据版本不匹配
			printf("Error------ERR_REPLYCODE_FEATURE_VERSION \n");
			break;
		case ERR_LACK_TWISTIMGE://- 61  //缺少归一化图像
			printf("Error------ERR_LACK_TWISTIMGE \n");
			break;
		case ERR_FUNC_AUTH://- 70   //功能授权失败
			printf("Error------ERR_FUNC_AUTH \n");
			break;
		case ERR_FUNC_AUTHORIZED://- 71   //功能已授权
			printf("Error------ERR_FUNC_AUTHORIZED \n");
			break;
		case ERR_UN_AUTH://- 72   //功能未授权
			printf("Error------ERR_UN_AUTH \n");
			break;
		case ERR_4GINFO://- 75   //获取4G信号消息失败
			printf("Error------ERR_PING_BLOCK \n");
			break;
		case ERR_PING_BLOCK://- 76   //ping网址失败
			printf("Error------ERR_PING_BLOCK \n");
			break;
		case ERR_WIFIUNCONNECTED://- 80   //wifi未连接
			printf("Error------ERR_WIFIUNCONNECTED \n");
			break;
		case ERR_UNKNOWN://- 1000 //未知错误
			printf("Error------ERR_UNKNOWN - 1000\n");
			break;
		default:
			printf("Error------ UKNOWCODE \n");
			break;
		}
	}
}