#include<iostream>
#include"gameManager.h"

int main() {
	int max, mafianum,port;
	cout << "방의 최대 인원수를 입력하세요 : ";
	cin >> max;
	cout << "마피아 수를 입력하세요 : ";
	cin >> mafianum;
	while (mafianum > (max / 2)) {
		cout << "마피아 수는 최대인원의 절반을 넘을 수 없습니다.\n";
		cout << "마피아 수를 입력하세요 : ";
		cin >> mafianum;
	}
	cout << "사용할 port번호를 입력하세요 : ";
	cin >> port;
	gameManager* game = new gameManager(max, mafianum,port);
	game->start();
	system("pause");
}