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

	cout << "서버 실행중..\n";
	while (1) {
		gameUser* newUser = gameroom->accept_func();
		//stringstream nick;
		//nick << "사용할 이름을 입력해주세요 : ";
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
		oss << "사용자가 입장했습니다.\n ";
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
	cout << "새 유저가 접속하였습니다.( " << this->userRoleList.size() << " / " << this->MaxUserNum << " )\n";
}

void gameManager::printUserBlock() {
	cout << "유저가 입장에 실패하였습니다.\n";
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
