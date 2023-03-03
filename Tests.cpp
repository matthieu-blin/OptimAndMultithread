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
	int s = X.exec("IE.exe src " #num, &src_duration); \
	int t = X.exec("IE.exe tst " #num, &tst_duration); \
	printf("Test " #num " : src duration : %I64d (%d), tst duration : %I64d (%d) \n", src_duration, s, tst_duration, t); \
	CHECK(s == t );\
	CHECK(src_duration > tst_duration)

TEST_CASE("Test1", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(1);
}
TEST_CASE("Test2", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(2);
}
TEST_CASE("Test3", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(3);
}
TEST_CASE("Test4", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(4);
}
TEST_CASE("Test5", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(5);
}
TEST_CASE("Test6", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(6);
}
TEST_CASE("Test7", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(7);
}
TEST_CASE("Test8", "[Optim]")
{
	EXEC_AND_COMPARE_DURATION(8);
}
TEST_CASE("Algo", "[Algo]")
{
	CHECK(X.exec("IE.exe tst  20", &tst_duration) == 1); 
}
TEST_CASE("Multithread", "[MultiThread]")
{
	CHECK(X.exec("IE.exe tst  21", &tst_duration) == 1); 
}

