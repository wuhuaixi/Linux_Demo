/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9.3 at Mon Oct 14 10:54:42 2019. */

#ifndef PB_NAZHI_PB_H_INCLUDED
#define PB_NAZHI_PB_H_INCLUDED
#include "pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _MsgType {
    MsgType_SendDataBack_tag = 0,
    MsgType_AddFcae_tag = 1,
    MsgType_FaceRecord_tag = 2,
    MsgType_OperationFaceId_tag = 3
} MsgType;
#define _MsgType_MIN MsgType_SendDataBack_tag
#define _MsgType_MAX MsgType_OperationFaceId_tag
#define _MsgType_ARRAYSIZE ((MsgType)(MsgType_OperationFaceId_tag+1))

/* Struct definitions */
typedef struct _DeviceId {
    char dev[32];
/* @@protoc_insertion_point(struct:DeviceId) */
} DeviceId;

typedef struct _NZ_Face {
    char faceID[20];
    char faceName[16];
    int32_t role;
    int32_t wgCardNO;
    int32_t effectTime;
    int32_t effectStartTime;
    int32_t version;
    int32_t wgCardNOLong;
    int32_t ScheduleMode;
    int32_t resv2;
    char userParam[68];
/* @@protoc_insertion_point(struct:NZ_Face) */
} NZ_Face;

typedef struct _Picture {
    char jpgName[20];
    int32_t jpgLengt;
    int32_t picId;
    int32_t libId;
    char libName[32];
/* @@protoc_insertion_point(struct:Picture) */
} Picture;

typedef struct _AddFcae {
    NZ_Face face;
    Picture picture;
/* @@protoc_insertion_point(struct:AddFcae) */
} AddFcae;

typedef struct _FaceRecord {
    NZ_Face face;
    Picture picture;
    DeviceId dev;
    int32_t tvSec;
    int32_t tvUsec;
    int32_t matched;
    int32_t sourceOfReg;
    int32_t living;
    int32_t hatColour;
/* @@protoc_insertion_point(struct:FaceRecord) */
} FaceRecord;

typedef struct _OperationFaceId {
    DeviceId dev;
    char faceId[20];
    int32_t operation;
/* @@protoc_insertion_point(struct:OperationFaceId) */
} OperationFaceId;

typedef struct _PhotoInfo {
    DeviceId Id;
    pb_callback_t protocol_ver;
    pb_callback_t firmware_ver;
    pb_callback_t code_ver;
    pb_callback_t build_time;
    pb_callback_t kernel_version;
    pb_callback_t lcd_type;
    pb_callback_t systemp_type;
    pb_callback_t plateform;
    pb_callback_t sensor_type;
    pb_callback_t algorithm_ver;
    pb_callback_t min_sdk_ver;
/* @@protoc_insertion_point(struct:PhotoInfo) */
} PhotoInfo;

typedef struct _SendDataBack {
    DeviceId Id;
    int32_t SeriNum;
    int32_t Error;
/* @@protoc_insertion_point(struct:SendDataBack) */
} SendDataBack;

/* Default values for struct fields */

/* Initializer values for message structs */
#define DeviceId_init_default                    {""}
#define SendDataBack_init_default                {DeviceId_init_default, 0, 0}
#define PhotoInfo_init_default                   {DeviceId_init_default, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}
#define NZ_Face_init_default                     {"", "", 0, 0, 0, 0, 0, 0, 0, 0, ""}
#define Picture_init_default                     {"", 0, 0, 0, ""}
#define AddFcae_init_default                     {NZ_Face_init_default, Picture_init_default}
#define FaceRecord_init_default                  {NZ_Face_init_default, Picture_init_default, DeviceId_init_default, 0, 0, 0, 0, 0, 0}
#define OperationFaceId_init_default             {DeviceId_init_default, "", 0}
#define DeviceId_init_zero                       {""}
#define SendDataBack_init_zero                   {DeviceId_init_zero, 0, 0}
#define PhotoInfo_init_zero                      {DeviceId_init_zero, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}
#define NZ_Face_init_zero                        {"", "", 0, 0, 0, 0, 0, 0, 0, 0, ""}
#define Picture_init_zero                        {"", 0, 0, 0, ""}
#define AddFcae_init_zero                        {NZ_Face_init_zero, Picture_init_zero}
#define FaceRecord_init_zero                     {NZ_Face_init_zero, Picture_init_zero, DeviceId_init_zero, 0, 0, 0, 0, 0, 0}
#define OperationFaceId_init_zero                {DeviceId_init_zero, "", 0}

/* Field tags (for use in manual encoding/decoding) */
#define DeviceId_dev_tag                         1
#define NZ_Face_faceID_tag                       1
#define NZ_Face_faceName_tag                     2
#define NZ_Face_role_tag                         3
#define NZ_Face_wgCardNO_tag                     4
#define NZ_Face_effectTime_tag                   5
#define NZ_Face_effectStartTime_tag              6
#define NZ_Face_version_tag                      7
#define NZ_Face_wgCardNOLong_tag                 8
#define NZ_Face_ScheduleMode_tag                 9
#define NZ_Face_resv2_tag                        10
#define NZ_Face_userParam_tag                    11
#define Picture_jpgName_tag                      1
#define Picture_jpgLengt_tag                     2
#define Picture_picId_tag                        3
#define Picture_libId_tag                        4
#define Picture_libName_tag                      5
#define AddFcae_face_tag                         1
#define AddFcae_picture_tag                      2
#define FaceRecord_face_tag                      1
#define FaceRecord_picture_tag                   2
#define FaceRecord_dev_tag                       3
#define FaceRecord_tvSec_tag                     4
#define FaceRecord_tvUsec_tag                    5
#define FaceRecord_matched_tag                   6
#define FaceRecord_sourceOfReg_tag               7
#define FaceRecord_living_tag                    8
#define FaceRecord_hatColour_tag                 9
#define OperationFaceId_dev_tag                  1
#define OperationFaceId_faceId_tag               2
#define OperationFaceId_operation_tag            3
#define PhotoInfo_Id_tag                         1
#define PhotoInfo_protocol_ver_tag               2
#define PhotoInfo_firmware_ver_tag               3
#define PhotoInfo_code_ver_tag                   4
#define PhotoInfo_build_time_tag                 5
#define PhotoInfo_kernel_version_tag             6
#define PhotoInfo_lcd_type_tag                   7
#define PhotoInfo_systemp_type_tag               8
#define PhotoInfo_plateform_tag                  9
#define PhotoInfo_sensor_type_tag                10
#define PhotoInfo_algorithm_ver_tag              11
#define PhotoInfo_min_sdk_ver_tag                12
#define SendDataBack_Id_tag                      1
#define SendDataBack_SeriNum_tag                 2
#define SendDataBack_Error_tag                   3

/* Struct field encoding specification for nanopb */
extern const pb_field_t DeviceId_fields[2];
extern const pb_field_t SendDataBack_fields[4];
extern const pb_field_t PhotoInfo_fields[13];
extern const pb_field_t NZ_Face_fields[12];
extern const pb_field_t Picture_fields[6];
extern const pb_field_t AddFcae_fields[3];
extern const pb_field_t FaceRecord_fields[10];
extern const pb_field_t OperationFaceId_fields[4];

/* Maximum encoded size of messages (where known) */
#define DeviceId_size                            34
#define SendDataBack_size                        58
/* PhotoInfo_size depends on runtime parameters */
#define NZ_Face_size                             198
#define Picture_size                             89
#define AddFcae_size                             292
#define FaceRecord_size                          394
#define OperationFaceId_size                     69

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define NAZHI_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif