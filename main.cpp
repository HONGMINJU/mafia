#include<iostream>
#include"gameManager.h"

int main() {
	int max, mafianum,port;
	cout << "���� �ִ� �ο����� �Է��ϼ��� : ";
	cin >> max;
	cout << "���Ǿ� ���� �Է��ϼ��� : ";
	cin >> mafianum;
	while (mafianum > (max / 2)) {
		cout << "���Ǿ� ���� �ִ��ο��� ������ ���� �� �����ϴ�.\n";
		cout << "���Ǿ� ���� �Է��ϼ��� : ";
		cin >> mafianum;
	}
	cout << "����� port��ȣ�� �Է��ϼ��� : ";
	cin >> port;
	gameManager* game = new gameManager(max, mafianum,port);
	game->start();
	system("pause");
}