#pragma once

#include <iostream>
#include <Windows.h>
#include"ExceptionClass.h"

class threadClass {
private:
	HANDLE hThread;
	DWORD  ThreadID;

	static DWORD WINAPI StaticThreadStart(LPVOID lpParam);

protected:
	virtual DWORD run(void) = 0;

public:
	threadClass() : hThread(NULL), ThreadID(0) {}

	void ThreadClose() {
		if (hThread) CloseHandle(hThread);
	}

	bool start();
	void join();
	bool isRunning();
};