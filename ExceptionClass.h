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
			cerr << "소켓 생성 에러\n";
			break;
		case 101:
			cerr << "소켓 바인딩 에러\n";
			break;
		case 102:
			cerr << "소켓 리스닝 에러\n";
			break;
		case 110:
			cerr << "세션 연결 에러\n";
			break;
		}
	}
};