#include"threadClass.h"

DWORD WINAPI threadClass::StaticThreadStart(LPVOID lpParam) {
	threadClass* pThread = (threadClass*)lpParam;
	return pThread->run();
}

bool threadClass::start() {
	if (hThread) {
		if (WaitForSingleObject(hThread, 0) == WAIT_TIMEOUT) {
			return false;
		}
		CloseHandle(hThread);
	}
	hThread = CreateThread(NULL,0,
		(LPTHREAD_START_ROUTINE)threadClass::StaticThreadStart,this,0,&ThreadID
	);

	if (hThread != NULL) return true;

	return false;
}

void threadClass::join() {
	::WaitForSingleObject(hThread, INFINITE);
}

bool threadClass::isRunning() {
	if (hThread) {
		DWORD dwExitCode = 0;
		::GetExitCodeThread(hThread, &dwExitCode);
		if (dwExitCode == STILL_ACTIVE) return true;
	}
	return false;
}