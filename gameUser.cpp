#include "gameUser.h";
#include "gameManager.h"

gameUser::gameUser(SOCKET socket, SOCKADDR_IN address) {
	this->user_socket = socket;
	this->user_address = address;
	this->strMaxLen = 255;
};
gameUser::~gameUser() {
	closesocket(this->user_socket);
	ThreadClose();
};

void gameUser::printUserLeave() {
	cout << "유저가 나갔습니다.\n";
};

char* gameUser::getIP() {
	char *address = inet_ntoa(this->user_address.sin_addr);
	return address;
};
int gameUser::getPort() {
	return ntohs(this->user_address.sin_port);
};
SOCKET gameUser::getSocket() {
	return this->user_socket;
};

void gameUser::receiveMsg(char *buf) {
	char msg[256];
	memset(&msg, 0, sizeof(msg));

	if (recv(this->user_socket, (char*)&msg, sizeof(msg), 0) <= 0) {
		throw ExceptionClass(110);
	}
	int len = strnlen(msg, strMaxLen);
	strncpy(buf, msg, len);
	buf[len] = 0;
};

void gameUser::sendMsg(SOCKET socket, const char *buf) {
	char msg[256];
	memset(&msg, 0, sizeof(msg));

	if (buf != nullptr) {
		int len = strnlen(buf, this->strMaxLen);
		strncpy(msg, buf, len);
		msg[len] = 0;
	}
	WaitForSingleObject(gameManager::mutex, INFINITE);
	if (send(socket, (const char*)&msg, sizeof(msg), 0) <= 0) {
		ReleaseMutex(gameManager::mutex);
		throw ExceptionClass(110);
	}
	ReleaseMutex(gameManager::mutex);
};
/*
void gameUser::setNickName(char *buf) {
	this->nickName = buf;
}
char* gameUser::getNickName() {
	return this->nickName;
};
*/
DWORD gameUser::run(void) {
	char buf[256];

	while (1) {
		try {
			receiveMsg(buf);
			stringstream oss;
			oss << this->getPort() << " >> " << buf;
			sendMessageExcept(oss.str().c_str(), this->getPort());
			cout << this->getPort() <<" >> " << buf << endl;
		}catch (ExceptionClass e) {
			stringstream oss;
			oss << this->getPort() <<" 사용자가 나갔습니다. ";
			sendMessageAll(oss.str().c_str());
			printUserLeave();
			break;
		}
	}
	WaitForSingleObject(gameManager::mutex, INFINITE);
	int len = gameManager::userRoleList.size();
	for (int i = 0; i<len; i++) {
		gameUser *user = gameManager::userRoleList.at(i)->user;
		if (user->getSocket() == this->getSocket()) {
			gameManager::userRoleList.erase(gameManager::userRoleList.begin() + i);
			break;
		}
	}
	ReleaseMutex(gameManager::mutex);
	delete this;
	return 0;
};
void gameUser::sendMessageAll(const char *buf) {
	int len = gameManager::userRoleList.size();
	for (int i = 0; i<len; i++) {
		gameUser *user = gameManager::userRoleList.at(i)->user;
		try {
			sendMsg(user->getSocket(), buf);
		}catch(ExceptionClass i){}
	}
};
void gameUser::sendMessageExcept(const char *buf,int port) {
	int len = gameManager::userRoleList.size();
	for (int i = 0; i<len; i++) {
		gameUser *user = gameManager::userRoleList.at(i)->user;
		if (user->getPort() == port) { continue; }
		try {
			sendMsg(user->getSocket(), buf);
		}
		catch (ExceptionClass i) {}
	}
};



