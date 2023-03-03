#pragma once

#pragma warning(push, 0)
#pragma warning(disable: 4868)
#include <chrono>
#include <windows.h>
#pragma warning(pop)

class Executor
{
public :
	Executor();
	int exec(char* _cmd, long long* _durationInMs);
private :
	std::chrono::time_point<std::chrono::system_clock> start, end;
	STARTUPINFOA si;
    PROCESS_INFORMATION pi;
};
