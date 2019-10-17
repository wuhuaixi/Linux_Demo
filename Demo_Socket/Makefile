#CPP=arm-hisiv600-linux-g++
CPP=g++

PROTO=pb_encode.cpp  pb_decode.cpp  pb_common.cpp  Server.cpp Nazhi.pb.c  Proto_NZ.cpp
777:
	$(CPP) -o Server ${PROTO}  -lpthread
PROTO_C= pb_encode.cpp  pb_decode.cpp  pb_common.cpp  Client.cpp  Nazhi.pb.c Proto_NZ.cpp
888:
	$(CPP) -o Client ${PROTO_C} -lpthread
	
999:
	for i in $(DIRS); do \
		(cd $$i && echo "making $$i" && $(MAKE) ) || exit 1; \
	done
	
all: client server

client:
	$(CPP) -o client Client.cpp
server:
	$(CPP) -o server Server.cpp
	
clean:
	rm -rf client
	rm -rf server
	rm -rf Server
	rm -rf Client

	


