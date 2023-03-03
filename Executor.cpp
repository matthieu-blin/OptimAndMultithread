#include "Executor.h"

Executor::Executor()
{
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
}

int Executor::exec(char* _cmd, long long* _durationInMs)
{
	start = std::chrono::system_clock::now();
	if (!CreateProcessA(NULL, _cmd, nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi))
		return -1;
	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);
	end = std::chrono::system_clock::now();
	// Close process and thread handles. 
	DWORD ec;
	GetExitCodeProcess(pi.hProcess, &ec);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	*_durationInMs = std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
	return ec;
}
