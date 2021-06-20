#pragma once
#include<iostream>
#include <vector>
#include <sstream>
#include"ExceptionClass.h"
#include "gameRoom.h"
#include "gameUser.h"
#include "ThreadClass.h"
#include <Windows.h>

using namespace std;

//struct nicKName_port {
//	char* nick;
//	int port;
//};

enum Role {people, mafia};

struct userRole {
	gameUser* user;
	Role role;
	userRole(gameUser* u) :user(u), role(people) {
	}
};

class gameManager {
private:
	gameRoom* gameroom;
public:
	gameManager(int maxNum,int mafianum,int port);
	int MaxUserNum;	//�� �ο���
	int mafiaNum;
	bool isGaming;

	void start();	//room ���� �� �ٷ� ���� �� �Լ�(bind, listen, accept, ...)
	void printUserIn();		
	void printUserBlock();	
	void printUserNum();	
	//static void pushNick(char* nick, int port);
	//static char* getNick(int port);
	//static vector<nicKName_port*> nickPort;
	static vector<userRole*> userRoleList;
	void pushUserRole(gameUser* u);
	static HANDLE mutex;	//critical section�� �� �� ���
};