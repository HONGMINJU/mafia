#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <WinSock2.h>
#include "threadClass.h"
#include"ExceptionClass.h"
using namespace std;

class gameUser  : public threadClass {
private:
	SOCKET user_socket;
	SOCKADDR_IN user_address;
	int strMaxLen;
	//char* nickName;

public:
	gameUser(SOCKET socket, SOCKADDR_IN address);
	gameUser(const gameUser &user) {}
	~gameUser();
	void operator=(const gameUser &user) {}

	//void setNickName(char *buf);
	//char* getNickName();

	char* getIP();
	int getPort();
	SOCKET getSocket();
	void printUserLeave();
	DWORD run(void);

	void receiveMsg(char *buf);
	void sendMsg(SOCKET socket, const char *buf = nullptr);

	void sendMessageAll(const char *buf = nullptr); 
	void sendMessageExcept(const char *buf, int port);
};