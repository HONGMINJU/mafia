#include"gameRoom.h"

gameRoom::gameRoom(const char *ip, int port) {

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData); //WS2_32.DLL을 초기화 , socket함수 호출 전에 실행해야 함

	this->room_socket = socket(AF_INET, SOCK_STREAM, 0);  //socket 생성 

	if (this->room_socket == INVALID_SOCKET) {
		throw ExceptionClass(100);
		WSACleanup();	//winsock사용을 중지, resource반환
	}
	// room_socket 주소설정
	memset(&this->room_address, 0, sizeof(this->room_address));
	if (ip != nullptr) {
		this->room_address.sin_addr.S_un.S_addr = inet_addr(ip);
	}
	else {
		this->room_address.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	}
	this->room_address.sin_port = htons(port);
	this->room_address.sin_family = AF_INET;
}

gameRoom::~gameRoom() {
	closesocket(this->room_socket); //client에 FIN packet전송
	WSACleanup(); 	//winsock사용 중지를 OS에 알림, resource반환
}

void gameRoom::bind_func() {
	if (bind(this->room_socket, (SOCKADDR*)&this->room_address, sizeof(this->room_address)) == SOCKET_ERROR) {
		cerr << "bind함수 에러\n";
	}
};
void gameRoom::listen_func(int maxNum) {
	if (listen(this->room_socket, maxNum) == SOCKET_ERROR) {
		cerr << "listen함수 에러\n";
	}
};
gameUser* gameRoom::accept_func() {

	SOCKET user_socket;
	SOCKADDR_IN user_address;
	int len = sizeof(user_address);
	user_socket = accept(this->room_socket, (SOCKADDR*)&user_address, &len);
	gameUser* newUser= new gameUser(user_socket, user_address);
	return newUser;

}
