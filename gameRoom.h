#pragma once
#include<iostream>
#include<WinSock2.h>
#include"ExceptionClass.h"
#include "gameUser.h"

using namespace std;

class gameRoom {
private:
	SOCKET room_socket;		//��������
	SOCKADDR_IN room_address;		//IPv4�ּ�ü�� ���

public:
	
	gameRoom(const char *ip=nullptr , int port=3490);	//maxNum:�� �ִ��ο�
	~gameRoom();

	void bind_func();
	void listen_func(int maxNum);
	gameUser* accept_func();

};
