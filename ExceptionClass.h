#pragma once
#include<iostream>
using namespace std;
class ExceptionClass {
public:
	int code;
	ExceptionClass(int n) {
		code = n;
	}
	void printErr() {
		switch(code){
		case 100:
			cerr << "���� ���� ����\n";
			break;
		case 101:
			cerr << "���� ���ε� ����\n";
			break;
		case 102:
			cerr << "���� ������ ����\n";
			break;
		case 110:
			cerr << "���� ���� ����\n";
			break;
		}
	}
};