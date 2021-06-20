#include"gameManager.h"
vector<userRole*> gameManager::userRoleList = vector<userRole*>();
//vector<nicKName_port*> gameManager::nickPort = vector<nicKName_port*>();
HANDLE gameManager::mutex = CreateMutex(NULL, FALSE, NULL);

gameManager::gameManager(int maxNum,int mafianum,int port) {
	this->MaxUserNum = maxNum;
	this->mafiaNum = mafianum;
	this->gameroom = new gameRoom(nullptr, port);
	this->isGaming = false;
}
void gameManager::start() {

	gameroom->bind_func();
	gameroom->listen_func(this->MaxUserNum);

	cout << "���� ������..\n";
	while (1) {
		gameUser* newUser = gameroom->accept_func();
		//stringstream nick;
		//nick << "����� �̸��� �Է����ּ��� : ";
		//newUser->sendMsg(newUser->getSocket(), nick.str().c_str());
		//char buf[25];
		//newUser->receiveMsg(buf);

		//WaitForSingleObject(this->mutex, INFINITE);
		//pushNick(buf, newUser->getPort());
		//ReleaseMutex(this->mutex);

		if (this->userRoleList.size() >= MaxUserNum) {
			printUserBlock();
			continue;
		}

		WaitForSingleObject(this->mutex, INFINITE);
		//this->userList.push_back(newUser); //critical section
		this->pushUserRole(newUser);
		ReleaseMutex(this->mutex);

		printUserIn();
		stringstream oss;
		oss << "����ڰ� �����߽��ϴ�.\n ";
		oss<< "============   ( " << this->userRoleList.size() << " / " << this->MaxUserNum << " )   ============\n";
		newUser->sendMessageAll(oss.str().c_str());
		newUser->start();
	}
}
void gameManager::pushUserRole(gameUser* u) {
	userRole* newRole=new userRole(u);
	this->userRoleList.push_back(newRole);
};
void gameManager::printUserIn() {
	cout << "�� ������ �����Ͽ����ϴ�.( " << this->userRoleList.size() << " / " << this->MaxUserNum << " )\n";
}

void gameManager::printUserBlock() {
	cout << "������ ���忡 �����Ͽ����ϴ�.\n";
}

void gameManager::printUserNum() {
	cout << "============   ( " << this->userRoleList.size() << " / " << this->MaxUserNum << " )   ============\n";
}

//	void gameManager::pushNick(char* nick, int port) {
//		nicKName_port* newNick = new nicKName_port;
//		newNick->nick = nick;
//		newNick->port = port;
//		nickPort.push_back(newNick);
//	};
//	char* gameManager::getNick(int port) {
//		for (nicKName_port* n : nickPort) {
//			if (n->port == port)return n->nick;
//		}
//	};
