
CPP=arm-hisiv600-linux-g++
INCLUDES = -I ../inc 
SHARE_LIB_PATH = -L ../lib/so
STATIC_LIB_PATH = -L ../lib/a
					
CFLAGS = $(INCLUDES) -g

TEST_A = test
TEST_SO = test
#lgomp
PROTO_C=Nazhi.pb.c  pb_encode.cpp  pb_decode.cpp  pb_common.cpp  test.cpp  Proto_NZ.cpp
STATIC_LIBS =$(STATIC_LIB_PATH) -lhasdk -lopencv_video -lopencv_highgui -lopencv_imgproc -lopencv_core -lzlib -lpthread -ldl -lgomp -llibpng -llibjpeg -lfacedetect -lncnn -lopenblas
#SHARE_LIBS = $(SHARE_LIB_PATH) -lhasdk
all : $(TEST_A) $(TEST_SO)

$(TEST_A):
	$(CPP) $(CFLAGS) -o $(TEST_A) ${PROTO_C} $(STATIC_LIBS)

#动态库暂不可用 请使用静态库
####$(TEST_SO):
#####$(CPP) $(CFLAGS) -o $(TEST_SO) test.cpp $(SHARE_LIBS)

install:
	$(SP) $(EXEC)	
	
clean:
	rm -rf $(TEST_A)
