#ifndef PKG_VEHICLE_H
#define PKG_VEHICLE_H


#define MAX_IMG_NUM 4
#define MAX_VIDEO_NUM 2
#define MAX_PLATE_IMG_NUM 2
#define MAX_FACE_IMG_NUM 32

/*
* @brief   ������Ϣ��
*/
struct pkg_vehicle {
	unsigned int sequence_id; // �����, ����
	unsigned int realtime_data; // -
	char packet_id[64]; // - ��ID

	char device_id[32];	// �豸���
	char addr_id[32];	// �ص���
	char direction_id[32]; // ������
	char camera_id[32];	// ������
	char lane_id[32];	// �������
	char addr_name[96];	// �ص�����
	char direction_name[96]; // ��������

	// ����, ��������, �������Ŷ�
	char plate[16];	// ���ƺ���, utf8����
	unsigned short plate_x; // �����ڻ����е����Ͻ�x����
	unsigned short plate_y; // �����ڻ����е����Ͻ�y����
	unsigned short plate_w;	// �����ڻ����е����ؿ��
	unsigned short plate_h; // �����ڻ����е����ظ߶�
	int plate_confidence;	// - ���Ŷ�

	unsigned char plate_color; // ������ɫ // 0-��ɫ 1-��ɫ 2-��ɫ 3-��ɫ 4-��ɫ 5-��ɫ 6-��ɫ 7-��ɫ(KISE)
	unsigned char vehicle_style; // - ��������
	unsigned char vehicle_color; // - ������ɫ
	unsigned char triger_type; // - ��������

	int redlight_begin_sec;
	int redlight_begin_usec;

	unsigned int system_type;
	unsigned int vio_type;

	unsigned short vehicle_speed;
	unsigned short limit_speed;

	int recoImageIndex;
	unsigned short vehicle_x[4];
	unsigned short vehicle_y[4];
	unsigned short vehicle_w[4];
	unsigned short vehicle_h[4];

	unsigned short red_lamp_x[4];      // 4���������
	unsigned short red_lamp_y[4];
	unsigned short red_lamp_w[4];
	unsigned short red_lamp_h[4];
	unsigned short vio_red_lamp_index; // ���ڵ���0ʱΪ��ǰ����ƶ�Ӧ������
	unsigned short direction;           // ������ʻ����
	char reserved[56];

	unsigned char img_num; // ����Я����ͼƬ��Ŀ
	unsigned char video_num; // ����Я������ƵƬ����Ŀ
	unsigned char plate_img_num; // ����Я���ĳ���ͼƬ��Ŀ
	unsigned char face_num; // ����Я��������ͼƬ��Ŀ

	unsigned int img_len[MAX_IMG_NUM]; // ��Ӧÿ��ͼƬ�ĳ���
	unsigned int video_len[MAX_VIDEO_NUM]; // ��Ӧÿ����Ƶ���ݵĳ���
	unsigned int plate_img_len[MAX_PLATE_IMG_NUM]; // ��Ӧÿ�ų���ͼƬ�ĳ���
	unsigned int face_img_len[MAX_FACE_IMG_NUM]; // ��Ӧÿ������ͼƬ�ĳ���

	char img_format[8];	// ͼƬ�ĸ�ʽ, ���� "jpg"
	char video_format[8]; // ��Ƶ��ʽ������ "avi"
	char plate_img_format[8]; // ����ͼƬ��ʽ������ "jpg"
	char face_img_format[8]; // ����ͼƬ��ʽ������ "jpg"

	int img_time_sec[MAX_IMG_NUM];
	int img_time_usec[MAX_IMG_NUM];

	int video_start_sec[MAX_VIDEO_NUM];
	int video_start_usec[MAX_VIDEO_NUM];
	int video_end_sec[MAX_VIDEO_NUM];
	int video_end_usec[MAX_VIDEO_NUM];

	unsigned short face_x[MAX_FACE_IMG_NUM];
	unsigned short face_y[MAX_FACE_IMG_NUM];
	unsigned short face_w[MAX_FACE_IMG_NUM];
	unsigned short face_h[MAX_FACE_IMG_NUM];

	unsigned char* img[MAX_IMG_NUM];
	unsigned char* video[MAX_VIDEO_NUM];
	unsigned char* plate_img[MAX_PLATE_IMG_NUM];
	unsigned char* face_img[MAX_FACE_IMG_NUM];
};

#endif