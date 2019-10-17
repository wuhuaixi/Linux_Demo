
#include "Proto_NZ.h"

using namespace std;

int QUERY_DELETE_FACE(uint8_t* send_pb, int* pbLength,int controll)
{
	OperationFaceId opertion = OperationFaceId_init_zero;

	sprintf(opertion.faceId, "%s_%d", "test_id", 3);
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
	return 0;
}
int QUERY_DELETE_FACE_REQ(pb_istream_t* istream)
{
	OperationFaceId opertion = OperationFaceId_init_zero;
	bool decode_status;
	decode_status = pb_decode(istream, OperationFaceId_fields, &opertion);
	if (!decode_status)
	{
		printf("pb_decode failed: %s\n", PB_GET_ERROR(istream));
		return -1;
	}
	printf("ddddd==%s\n", opertion.faceId);
	printf("ddddd==%d\n", opertion.operation);
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
}
int HA_ADD_FACE(uint8_t* send_pb,int* pbLength)
{
	AddFcae mAddFcae= AddFcae_init_zero;
	sprintf(mAddFcae.face.faceID, "%s_%d", "test_id", 1);
	sprintf(mAddFcae.face.faceName, "%s", "ÌìÑÄ");
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
	return 0;
}

