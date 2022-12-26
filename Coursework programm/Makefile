target = client
sources = main.cpp User.h Interface.cpp User.cpp UserHandler.cpp TCPclient.cpp 
CC = g++
CCFlags = -Wall
LDLIBS = -lstdc++fs -lcrypto++ -lboost_system
OPT = -Ofast
all:build
build:
	$(CC) $(CCFlags) $(OPT) $(sources) -o $(target) $(LDLIBS)
dbg:
	$(CC) -g $(sources) -o $(target)DBG
cls:
	del *.exe

