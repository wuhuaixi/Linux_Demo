#ifndef PROTO_NZ_H
#define PROTO_NZ_H



#include <arpa/inet.h>
#include<errno.h>
#include<fstream>
#include <fcntl.h>
#include <iostream>
#include<netinet/in.h>
#include<netdb.h>
#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
#include <signal.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include <unistd.h>

#include "pb_encode.h"
#include "pb_decode.h"
#include "Nazhi.pb.h"
#include "pb.h"

#define MATCHED_DEGRESS             80    //Ä¬ÈÏÆ¥Åä¶È

int HA_ADD_FACE_REQ(pb_istream_t* istream);
int HA_ADD_FACE(uint8_t* send_pb, int* pbLength);

int QUERY_DELETE_FACE(uint8_t* send_pb, int* pbLength, int controll);
int QUERY_DELETE_FACE_REQ(pb_istream_t* istream);



#endif