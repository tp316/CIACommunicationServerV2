INSTALL_DIR = /home/lyl/openlib
CC = g++ -D_LINUX -std=c++11 -D_REENTRANT -lpthread -lshpa3 -lcurses
INCLUDE_DIR =-I $(INSTALL_DIR)/boost/include -I $(INSTALL_DIR)/protocol_buffer/include -I . -I /usr/local/lib/shcti/ver5.3.31/out 
LIB_DIR = -L$(INSTALL_DIR)/boost/lib -L/usr/local/lib/shcti/ver5.3.31/out

all : main_test_cti.o

CiaProtocol.pb.cc : 
	$(INSTALL_DIR)/bin/protoc --cpp_out=. ./net_logic/CiaProtocol.proto

#boost_log.o :
#	$(CC) -I $(INSTALL_DIR)/boost/include -L $(INSTALL_DIR)/boost/lib ./tools/boost_log.hpp -o ./obj/boost_log.o

#chat_message.o : CiaProtocol.pb.cc
#	$(CC) -I $(INSTALL_DIR)/include -I ./net_logic ./net_logic/chat_message.hpp -o ./obj/chat_message.o

#base_client.o : chat_message.o boost_log.o
#	$(CC) ./net_logic/base_client.hpp -o ./obj/base_client.o

main_test_cti.o :
	$(CC) $(INCLUDE_DIR) $(LIB_DIR) -o main_test_cti.o main_test_cti.cpp

%.o : %.cpp
	gcc -c $<

%.o : %.c
	gcc -c $<

clean :
	rm -rf *.o
