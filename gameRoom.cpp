#include"gameRoom.h"

gameRoom::gameRoom(const char *ip, int port) {

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData); //WS2_32.DLL�� �ʱ�ȭ , socket�Լ� ȣ�� ���� �����ؾ� ��

	this->room_socket = socket(AF_INET, SOCK_STREAM, 0);  //socket ���� 

	if (this->room_socket == INVALID_SOCKET) {
		throw ExceptionClass(100);
		WSACleanup();	//winsock����� ����, resource��ȯ
	}
	// room_socket �ּҼ���
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
	closesocket(this->room_socket); //client�� FIN packet����
	WSACleanup(); 	//winsock��� ������ OS�� �˸�, resource��ȯ
}

void gameRoom::bind_func() {
	if (bind(this->room_socket, (SOCKADDR*)&this->room_address, sizeof(this->room_address)) == SOCKET_ERROR) {
		cerr << "bind�Լ� ����\n";
	}
};
void gameRoom::listen_func(int maxNum) {
	if (listen(this->room_socket, maxNum) == SOCKET_ERROR) {
		cerr << "listen�Լ� ����\n";
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
