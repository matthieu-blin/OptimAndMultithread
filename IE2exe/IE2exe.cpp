// IE2exe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include "Source.h"
#include "Test.h"
#include "RepasChinois.h"

using namespace std;

int main(int argc, char* argv[])
{

	bool src = argc > 2 ? strcmp(argv[1], "src") == 0 : false;
	int testcase = argc> 2 ? atoi(argv[2]) : 9;
	switch (testcase)
	{
	case 0 :
	{
		if (src)
		{
			Source::Test0 src;
			for (int i = 0; i < 100000; ++i)
				src._GenerateNewPlayer();
		}
		else
		{
			Test::Test0 test;
			for (int i = 0; i < 100000; ++i)
				test._GenerateNewPlayer();
		}
		return 1;
	}
	case 1:
	{
		if (src)
		{
			char* result = nullptr;
			Source::Test1 src;
			src.FillWithFakeResources(100000);
			for (int i = 0; i < 10000; ++i)
			{
				result = src.FindData(std::rand());
			}
			return result != nullptr ? 1 : 2;

		}
		else
		{
			char* result = nullptr;
			Test::Test1 src;
			src.FillWithFakeResources(100000);
			for (int i = 0; i < 10000; ++i)
			{
				result = src.FindData(std::rand());
			}
			return result != nullptr ? 1 : 2;
		}
		return 1;
	}
	case 2:
	{
		if (src)
		{
			Source::Test2 src;
			for (int i = 0; i < 10000; ++i)
			{
				src.InsertPlayer(std::rand(), ((float)std::rand() / RAND_MAX) * 2500.f);
			}
			bool found = false;
			for (int i = 0; i < 10000; ++i)
			{
				long long uid = src.FindNearestAdversary(((float)std::rand() / RAND_MAX) * 2500.f);
				if (uid > 0)
					found = true;
			}
			return found ? 1 : 2;

		}
		else
		{
			Test::Test2 src;
			for (int i = 0; i < 10000; ++i)
			{
				src.InsertPlayer(std::rand(), ((float)std::rand() / RAND_MAX) * 2500.f);
			}
			bool found = false;
			for (int i = 0; i < 10000; ++i)
			{
				long long uid = src.FindNearestAdversary(((float)std::rand() / RAND_MAX) * 2500.f);
				if (uid > 0)
					found = true;
			}
			return found ? 1 : 2;
		}
		return 1;
	}
	case 3:
	{
		if (src)
		{
			Source::Test3 src;
			for (int i = 0; i < 5000000; ++i)
			{
				src.InsertPosition(Source::Test3::_Vector3{i*1.0f, i*0.5f, i*1.7f});
			}
		}
		else
		{
			Test::Test3 src;
			for (int i = 0; i < 5000000; ++i)
			{
				src.InsertPosition(Test::Test3::_Vector3{i*1.0f, i*0.5f, i*1.7f});
			}
		}
		return 1;
	}
	case 4:
	{
		std::vector<std::function<bool()>> conditions;
		static std::function<bool()> randCondition = []()->bool
		{
			return std::rand() % 2 == 0;
		};
		conditions.push_back(randCondition);
		if (src)
		{
			Source::Test4 src;
			for (int i = 0; i < 100000; ++i)
			{
				src.InsertNewPlayerAtConditions(conditions);
			}
		}
		else
		{
			Test::Test4 src;
			for (int i = 0; i < 100000; ++i)
			{
				src.InsertNewPlayerAtConditions(conditions);
			}
		}
		return 1;
	}
	case 5: 
	{
		for (int i = 0; i < 1000000; ++i)
		{
			if (src)
				Source::Test5::ComputeString((i % 4) + 97, "name");
			else
				Test::Test5::ComputeString((i % 4) + 97, "name");
		}
		return 1;
	}
	case 6: 
	{
		if (src)
		{
			Source::Test6 tst;
			tst._InsertXMob(1000);
			tst._InsertXPlayer(1000);
			for (int i = 0; i < 10000; ++i)
			{
				tst.ImpulseAll(i * 0.1f, i * 0.1f);
			}

		}
		else
		{
			Test::Test6 tst;
			tst._InsertXMob(1000);
			tst._InsertXPlayer(1000);
			for (int i = 0; i < 10000; ++i)
			{
				tst.ImpulseAll(i * 0.1f, i * 0.1f);
			}

		}
		return 1;
	}
	case 7:
	{
		if (src)
		{
			Source::Test7 tst;
			tst._InsertXEntity(1000);
			for (int i = 0; i < 100000; ++i)
			{
				tst.MoveAllEntities(i * 0.1f, i * 0.1f);
			}
		}
		else
		{
			Test::Test7 tst;
			tst._InsertXEntity(1000);
			for (int i = 0; i < 100000; ++i)
			{
				tst.MoveAllEntities(i * 0.1f, i * 0.1f);
			}
		}
		return 1;
	}
	case 8:
	{
		if (src)
		{
			Source::Test8::LargeMatrix A;
			Source::Test8::LargeMatrix B;
			Source::Test8::LargeMatrix C;
			for (int i = 0; i < 100; ++i)
			{
				if (i % 10 == 0)
				{
					Source::Test8::_RandMatrix(A);
					Source::Test8::_RandMatrix(B);
				}
				Source::Test8::MultiplyMatrix(A, B, C);
			}
		}
		else
		{
			Test::Test8::LargeMatrix A;
			Test::Test8::LargeMatrix B;
			Test::Test8::LargeMatrix C;
			for (int i = 0; i < 100; ++i)
			{
				if (i % 10 == 0)
				{
					Test::Test8::_RandMatrix(A);
					Test::Test8::_RandMatrix(B);
				}
				Test::Test8::MultiplyMatrix(A, B, C);
			}
		}
		return 1;
	}
	case 9: 
	{
		if (src)
		{
			unsigned int res = 0;
			Source::Test9 tst;
			tst._InitializeRandomValue();
			for (int i = 0; i < 1000000; ++i)
			{
				res += tst.FindNearestRandom(std::rand() % 255);
			}
			return res;
		}
		else
		{
			unsigned int res = 0;
			Test::Test9 tst;
			tst._InitializeRandomValue();
			for (int i = 0; i < 1000000; ++i)
			{
				res += tst.FindNearestRandom(std::rand() % 255);
			}
			return res;

		}
		return 1;
	}

	case 10: 
	{
		constexpr char* resources[] = {
		 "c:\file0.txt"
		, "c:\file1.txt"
		, "c:\file2.txt"
		, "c:\file3.txt"
		, "c:\file4.txt"
		, "c:\file5.txt"
		, "c:\file6.txt"
		, "c:\file7.txt"
		, "c:\file8.txt"
		, "c:\file9.txt"
		, "c:\file0.txt"
		, "c:\file11.txt"
		, "c:\file12.txt"
		, "c:\file13.txt"
		, "c:\file14.txt"
		, "c:\file15.txt"
		, "c:\file16.txt"
		, "c:\file17.txt"
		, "c:\file18.txt"
		, "c:\file19.txt"
		, "c:\file20.txt"
		, "c:\file21.txt"
		, "c:\file22.txt"
		, "c:\file23.txt"
		, "c:\file24.txt"
		, "c:\file25.txt"
		, "c:\file26.txt"
		, "c:\file27.txt"
		, "c:\file28.txt"
		, "c:\file29.txt"
		, "c:\file30.txt"
		, "c:\file31.txt"
		, "c:\file32.txt"
		, "c:\file33.txt"
		, "c:\file34.txt"
		, "c:\file35.txt"
		, "c:\file36.txt"
		, "c:\file37.txt"
		, "c:\file38.txt"
		, "c:\file39.txt" 
		, "c:\file40.txt"
		, "c:\file41.txt"
		, "c:\file42.txt"
		, "c:\file43.txt"
		, "c:\file44.txt"
		, "c:\file45.txt"
		, "c:\file46.txt"
		, "c:\file47.txt"
		, "c:\file48.txt"
		, "c:\file49.txt" 
		};
		unsigned long long t = 0;
		if (src)
		{
			Source::Test10 tst;
			tst._InitResource((const char**)resources, 50);
			for (int i = 0; i < 20; ++i)
			{
				char* data = tst.GetData(resources[std::rand() % 40]);
				t += (unsigned long long)data;
			}
			return t;
		}
		else
		{
			Test::Test10 tst;
			tst._InitResource((const char**)resources, 50);
			for (int i = 0; i < 20; ++i)
			{
				char* data = tst.GetData(resources[std::rand() % 40]);
				t += (unsigned long long)data;
			}
			return t;
		}
		return 1;
	}
	case 11:
	{
		RepasChinois repas;
		repas.MettreLaTable();
		repas.Manger();
		return 1;
	}
	}
	return -1;
}

