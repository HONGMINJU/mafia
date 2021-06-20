#pragma once
#include<iostream>
#include<WinSock2.h>
#include"ExceptionClass.h"
#include "gameUser.h"

using namespace std;

class gameRoom {
private:
	SOCKET room_socket;		//서버소켓
	SOCKADDR_IN room_address;		//IPv4주소체계 사용

public:
	
	gameRoom(const char *ip=nullptr , int port=3490);	//maxNum:방 최대인원
	~gameRoom();

	void bind_func();
	void listen_func(int maxNum);
	gameUser* accept_func();

};
