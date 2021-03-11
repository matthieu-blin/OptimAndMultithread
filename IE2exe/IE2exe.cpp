// IE2exe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include "Source.h"
#include "Test.h"


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
		if (src)
		{
			Source::Test11 tst; 
			int result = 0;

			int n = 100000;
			while (--n, n >= 0)
			{
				result += tst.SumAllDigits("0123456789");//45
				result += tst.SumAllDigits("le chien a mangé 10 bonnes croquettes");
				result += tst.SumAllDigits("qwettytuytiyo32`321532vcx456sf1è2`trey");
				result += tst.SumAllDigits("Le Trône de fer (A Song of Ice and Fire) est une série de romans de fantasy de George R. R. Martin, dont l'écriture et la parution sont en cours. Martin a commencé à l'écrire en 1991 et le premier volume est paru en 1996 chez Bantam Books. Prévue à l'origine comme une trilogie, la série compte désormais cinq volumes publiés et deux autres sont attendus (les tomes ont ensuite été redécoupés dans la traduction française).  L'histoire se déroule dans un monde imaginaire où la société est de type féodal et où la magie et des créatures légendaires (telles que les dragons) ont existé mais sont censées avoir disparu. Trois intrigues principales s'y entremêlent : dans le royaume des Sept Couronnes, plusieurs maisons nobles rivalisent pour l'obtention du trône ; dans les contrées glacées situées au nord du royaume, une race de créatures supposée appartenir aux légendes se réveille ; et sur le continent oriental, la dernière héritière des Targaryen (la dynastie royale des Sept Couronnes renversée quinze ans auparavant), cherche à reconquérir le trône.  Chaque chapitre est présenté à travers le point de vue de l'un des personnages principaux. Les thèmes abordés sont plus réalistes que dans la fantasy traditionnelle. Les quelque vingt personnages principaux présentent souvent un comportement d'une moralité ambiguë, et les intrigues politiques et les renversements de situation sont fréquents.La violence et la sexualité occupent aussi des places importantes. ");

			}
			return result;
		}
		else
		{
			Test::Test11 tst;
			int result = 0;
			int n = 100000;
			while (--n, n >= 0)
			{
				result += tst.SumAllDigits("0123456789");//45
				result += tst.SumAllDigits("le chien a mangé 10 bonnes croquettes");
				result += tst.SumAllDigits("qwettytuytiyo32`321532vcx456sf1è2`trey");
				result += tst.SumAllDigits("Le Trône de fer (A Song of Ice and Fire) est une série de romans de fantasy de George R. R. Martin, dont l'écriture et la parution sont en cours. Martin a commencé à l'écrire en 1991 et le premier volume est paru en 1996 chez Bantam Books. Prévue à l'origine comme une trilogie, la série compte désormais cinq volumes publiés et deux autres sont attendus (les tomes ont ensuite été redécoupés dans la traduction française).  L'histoire se déroule dans un monde imaginaire où la société est de type féodal et où la magie et des créatures légendaires (telles que les dragons) ont existé mais sont censées avoir disparu. Trois intrigues principales s'y entremêlent : dans le royaume des Sept Couronnes, plusieurs maisons nobles rivalisent pour l'obtention du trône ; dans les contrées glacées situées au nord du royaume, une race de créatures supposée appartenir aux légendes se réveille ; et sur le continent oriental, la dernière héritière des Targaryen (la dynastie royale des Sept Couronnes renversée quinze ans auparavant), cherche à reconquérir le trône.  Chaque chapitre est présenté à travers le point de vue de l'un des personnages principaux. Les thèmes abordés sont plus réalistes que dans la fantasy traditionnelle. Les quelque vingt personnages principaux présentent souvent un comportement d'une moralité ambiguë, et les intrigues politiques et les renversements de situation sont fréquents.La violence et la sexualité occupent aussi des places importantes. ");
			}
			return result;
		}
		return 1;
	}

	case 12 :
	{
		if (src)
		{
			Source::Test12 tst;
			int result = 0;

			int n = 1000000;
			while (--n, n >= 0)
			{
				unsigned long pArray[] = { 1,2,3,4,5 };
				unsigned long pArray2[] = { 788, 432,43 ,14321,43214,5437,6584,876,978,9871,870,9870,98097,72,5432, 783, 4966, 4984613, 849, 1256, 16516, 1686, 16168, 156184, 616513784 };
				unsigned long newsize = tst.filterArray(pArray, 5);
				for (int i = 0; i < newsize; i++)
				{
					result += pArray[i];
				}

				newsize = tst.filterArray(pArray2, sizeof(pArray2) / sizeof(long));
				for (int i = 0; i < newsize; i++)
				{
					result += pArray2[i];
				}
			}
			return result;
		}
		else
		{
			Test::Test12 tst;
			int result = 0;

			int n = 1000000;
			while (--n, n >= 0)
			{
				unsigned long pArray[] = { 1,2,3,4,5 };
				unsigned long pArray2[] = { 788, 432,43 ,14321,43214,5437,6584,876,978,9871,870,9870,98097,72,5432, 783, 4966, 4984613, 849, 1256, 16516, 1686, 16168, 156184, 616513784 };
				unsigned long newsize = tst.filterArray(pArray, 5);
				for (int i = 0; i < newsize; i++)
				{
					result += pArray[i];
				}

				newsize = tst.filterArray(pArray2, sizeof(pArray2) / sizeof(long));
				for (int i = 0; i < newsize; i++)
				{
					result += pArray2[i];
				}
			}
			return result;
		}
		return 0;

	}

	case 14 :
	{
		int n = 1000;
		while (--n, n != 0)
		{
			if (src)
				Source::Sample::Exec();
			else
				Test::Sample::Exec();
		}
		return 1;
	}
	}
	return -1;
}

