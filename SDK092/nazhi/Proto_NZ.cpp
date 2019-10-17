
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
	sprintf(mAddFcae.face.faceName, "%s", "����");
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
		case ERR_NONE://                    0    //�޴���
			printf("Error------ERR_NONE \n");
			break;
		case ERR_INVALID_PARAM: //://- 1   //���Ϸ���ֵ
			printf("Error------ERR_INVALID_PARAM \n");
			break;
		case ERR_TIMEOUT://- 2   //��Ӧ��ʱ
			printf("Error------ERR_TIMEOUT \n");
			break;
		case ERR_SEND_BUF_FULL://- 3   //���ͻ�������
			printf("Error------ERR_SEND_BUF_FULL \n");
			break;
		case ERR_SYS_NOT_MATCH://- 4   //����
			printf("Error------ERR_SYS_NOT_MATCH \n");
			break;
		case ERR_UNCONNECTED://- 5   //���δ����
			printf("Error------ERR_UNCONNECTED \n");
			break;
		case ERR_SNAPSHOT_UNAVAILABLE://- 6   //��ͼʧ��
			printf("Error------ERR_SNAPSHOT_UNAVAILABLE \n");
			break;
		case ERR_JPEG_ENCODE_ERROR://- 7   //JPEG����ʧ��
			printf("Error------JPEGERR_JPEG_ENCODE_ERROR \n");
			break;
		case ERR_BUF_TOO_SMALL://- 8   //����ռ䲻��
			printf("Error------ERR_BUF_TOO_SMALL \n");
			break;
		case ERR_CANCEL://- 9   //����
			printf("Error------ERR_CANCEL \n");
			break;
		case ERR_UNABLE_TO_OPEN_FILE:    //- 10  //�ļ���ʧ��
			printf("Error------ERR_UNABLE_TO_OPEN_FILE \n");
			break;
		case ERR_DEVICE_NOT_SUPPORTED://- 11  //�豸��֧��
			printf("Error------ERR_DEVICE_NOT_SUPPORTED \n");
			break;
		case ERR_COUNT_INVALID://- 12  //����
			printf("Error------ERR_COUNT_INVALID \n");
			break;
		case ERR_OUT_PUT_OF_ARRAY://- 13  //����
			printf("Error------ERR_OUT_PUT_OF_ARRAY \n");
			break;
		case ERR_GET_FACE_FEATURE://- 14   //��ȡ��������ʧ�ܣ��뱣֤ͼ�������ҽ���һ������
			printf("Error------ERR_GET_FACE_FEATURE \n");
			break;
		case ERR_FACE_ID_REPEAT://- 15   //�����Աʧ�ܣ���Աid�ظ�
			printf("Error------ERR_FACE_ID_REPEAT \n");
			break;
		case ERR_FACE_ID_NOT_EXITS://- 16   //�޸���������ʧ�ܣ�δ�ҵ���ӦID
			printf("Error------ERR_FACE_ID_NOT_EXITS \n");
			break;
		case ERR_GET_FACE_INIT://- 17   //������ȡ��δ��ʼ���������HA_InitFaceModel��ʼ��
			printf("Error------ERR_GET_FACE_INIT \n");
			break;
		case ERR_GET_FACE_ID://- 18   //�޵�ǰ��¼
			printf("Error------ERR_GET_FACE_ID \n");
			break;
		case ERR_SERIAL_INDEX://- 19   //����Ĵ��ڱ�ţ�Ŀǰֻ֧��HA_SERIAL_RS485��HA_SERIAL_RS232
			printf("Error------ERR_SERIAL_INDEX \n");
			break;
		case ERR_SYSTEM_REBOOT://- 20   //����ϵͳʧ��
			printf("Error------ERR_SYSTEM_REBOOT \n");
			break;
		case ERR_APP_REBOOT://- 21   //����Ӧ�ó���ʧ��
			printf("Error------ERR_APP_REBOOT \n");
			break;
		case ERR_ENCODE_JPG://- 22   //ѹ��ͼ��ʧ��
			printf("Error------ERR_ENCODE_JPG \n");
			break;
		case ERR_FACES_NUM://- 23   //������Ա���֧��5��ͼ��
			printf("Error------ERR_FACES_NUM \n");
			break;
		case ERR_IMAGE_DECODE://- 24   //ͼ�����ʧ��
			printf("Error------ERR_IMAGE_DECODE \n");
			break;
		case ERR_IMAGE_SIZE://- 25   //ͼ��̫��������ȡ������jpgͼ���ܳ���10M��jpg ֱ��ע��ͼ�񲻳���6M 
			printf("Error------ERR_IMAGE_SIZE  \n");
			break;
		case ERR_IMAGE_PATH://- 26   //�ļ������ڣ�����ͼƬ·���Ƿ���ȷ
			printf("Error------ERR_IMAGE_PATH\n");
			break;
		case ERR_SAVE_IMG_NUM://- 27   //Ŀǰ���ֻ֧�ִ�һ��ģ��ͼ��pictureFlags����<=1
			printf("Error------ERR_SAVE_IMG_NUM\n");
			break;
		case ERR_PTZ_CTRL://- 28   //��֧�ֵ���̨���ƣ�Ŀǰֻ֧��5���䱶���Ŵ� 6���䱶����С�� 7���۽��������� 8���۽�����Զ��
			printf("Error------ERR_PTZ_CTRL\n");
			break;
		case ERR_PTZ_CTRL_MODE://- 29   //��֧�ֵĿ���ģʽ��1��һ���˶� 2������ 3��ֹͣ
			printf("Error------ERR_PTZ_CTRL_MODE \n");
			break;
		case ERR_DAEMON_REQUEST://- 30   //����
			printf("Error------ERR_DAEMON_REQUEST \n");
			break;
		case ERR_UPPER_LIMIT://- 31   //��Ա�����Ѵ�����
			printf("Error------ERR_UPPER_LIMIT \n");
			break;
		case ERR_PROTOCAL_VER://- 32   //Э��汾��ƥ�䣬��ȷ��SDK������̼��汾
			printf("Error------ERR_PROTOCAL_VER\n");
			break;
		case ERR_REQUEST_CMD://- 33   //��֧�ֵĲ�������
			printf("Error------ERR_REQUEST_CMD \n");
			break;
		case ERR_PACKET_DATA://- 34   //�������ݰ��������Ϸ��ֶ�
			printf("Error------ERR_PACKET_DATA \n");
			break;
		case ERR_AUTH_FAILED://- 35   //��֤ʧ��
			printf("Error------ERR_AUTH_FAILED \n");
			break;
		case ERR_WRITE_DATA://- 36   //д������ʧ��
			printf("Error------ERR_WRITE_DATA \n");
			break;
		case ERR_READ_DATA://- 37   //��ȡ����ʧ��
			printf("Error------ERR_READ_DATA \n");
			break;
		case ERR_TWIST_FACE://- 38   //��һ��ͼ��ʧ��
			printf("Error------ERR_TWIST_FACE \n");
			break;
		case ERR_EXTRACT_FEATURE://- 39   //��ȡ����ʧ��
			printf("Error------ERR_EXTRACT_FEATURE \n");
			break;
		case ERR_MIN_FACE://- 40   //�����ߴ�̫С�����������������96*96
			printf("Error------ERR_MIN_FACE \n");
			break;
		case ERR_QVALUE_TOO_SMALL://- 41   //��������̫�����ע������
			printf("Error------ERR_QVALUE_TOO_SMALL \n");
			break;
		case ERR_INVALID_SYNC_MODE://- 42   //��Ч��ͬ������
			printf("Error------ERR_INVALID_SYNC_MODE \n");
			break;
		case ERR_WG_QUERY_MODE://- 43   //Τ�����Ų�֧��ģ����ѯ
			printf("Error------ERR_WG_QUERY_MODE\n");
			break;
		case ERR_SYSTEM_BUSY://- 44   //����ϵͳ��æ
			printf("Error------ERR_SYSTEM_BUSY\n");
			break;
		case ERR_VERSION_MATCH://- 45   //�汾��ƥ��
			printf("Error------ERR_VERSION_MATCH\n");
			break;
		case ERR_TOO_MUCH_FACE://- 46   //ͼ������������Ϊ1
			printf("Error------ERR_TOO_MUCH_FACE \n");
			break;
		case ERR_FACE_INCOMPLETE://- 47     //ͼ��������������
			printf("Error------ERR_FACE_INCOMPLETE \n");
			break;
		case ERR_ANGLE_PITCH://- 48     //����������̫��
			printf("Error------ERR_ANGLE_PITCH \n");
			break;
		case ERR_ANGLE_YAW://- 49     //������ƫ��̫��
			printf("Error------ERR_ANGLE_YAW \n");
			break;
		case ERR_ANGLE_ROLL://- 50     //��������
			printf("Error------ERR_ANGLE_ROLL \n");
			break;
		case ERR_MOUTH_OPEN://- 51     //������ȹ���
			printf("Error------ERR_MOUTH_OPEN \n");
			break;
		case ERR_YINYANG_FACE://- 52     //���ղ�����
			printf("Error------ERR_YINYANG_FACE \n");
			break;
		case ERR_VISIBLE_TARGET://- 54    // δ���ָ�������ɼ���Ŀ��*/
			printf("Error------ERR_VISIBLE_TARGET \n");
			break;
		case ERR_INFRARED_TARGET://- 55    //δ���ָ�����������Ŀ��*/
			printf("Error------ERR_INFRARED_TARGET \n");
			break;
		case ERR_ABERRATION_TOO_BIG://- 56     // �ɼ�������������*/
			printf("Error------ERR_ABERRATION_TOO_BIG \n");
			break;
		case ERR_REPLYCODE_FEATURE_VERSION://- 60  //�������ݰ汾��ƥ��
			printf("Error------ERR_REPLYCODE_FEATURE_VERSION \n");
			break;
		case ERR_LACK_TWISTIMGE://- 61  //ȱ�ٹ�һ��ͼ��
			printf("Error------ERR_LACK_TWISTIMGE \n");
			break;
		case ERR_FUNC_AUTH://- 70   //������Ȩʧ��
			printf("Error------ERR_FUNC_AUTH \n");
			break;
		case ERR_FUNC_AUTHORIZED://- 71   //��������Ȩ
			printf("Error------ERR_FUNC_AUTHORIZED \n");
			break;
		case ERR_UN_AUTH://- 72   //����δ��Ȩ
			printf("Error------ERR_UN_AUTH \n");
			break;
		case ERR_4GINFO://- 75   //��ȡ4G�ź���Ϣʧ��
			printf("Error------ERR_PING_BLOCK \n");
			break;
		case ERR_PING_BLOCK://- 76   //ping��ַʧ��
			printf("Error------ERR_PING_BLOCK \n");
			break;
		case ERR_WIFIUNCONNECTED://- 80   //wifiδ����
			printf("Error------ERR_WIFIUNCONNECTED \n");
			break;
		case ERR_UNKNOWN://- 1000 //δ֪����
			printf("Error------ERR_UNKNOWN - 1000\n");
			break;
		default:
			printf("Error------ UKNOWCODE \n");
			break;
		}
	}
}