#pragma warning(push, 0)
#pragma warning(disable: 4868)
#include "catch.h"
#include <chrono>
#include <windows.h>
#include "Executor.h"
#pragma warning(pop)

Executor X;
long long src_duration = 0;
long long tst_duration = 0;

#define EXEC_AND_COMPARE_DURATION(num) \
	CHECK(X.exec("IE2exe.exe src " #num, &src_duration)); \
	CHECK(X.exec("IE2exe.exe tst " #num, &tst_duration)); \
	printf("Test " #num " : src duration : %I64d , tst duration : %I64d\n", src_duration, tst_duration); \
	CHECK(src_duration > tst_duration)

TEST_CASE("Fastest than copy ?", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(0);
}

TEST_CASE("Around Container 1", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(1);
}

TEST_CASE("Around Container 2", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(2);
}

TEST_CASE("Classic issue", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(3);
}

TEST_CASE("Classic issue 2", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(4);
}

TEST_CASE("Classic issue 3", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(5);
}

TEST_CASE("around vtable ", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(6);
}

TEST_CASE("Classic issue 4, the come back", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(7);
}

TEST_CASE("About Memory", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(8);
}

TEST_CASE("Classic issue 5", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(9);
}

TEST_CASE("Classic issue 6", "[Optim]")
{
	CHECK(X.exec("IE2exe.exe tst  11", &tst_duration)); 
	printf("Test 11 : duration : %I64d \n", tst_duration); 
}