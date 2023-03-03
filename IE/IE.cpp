#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include "Source.h"
#include "Test.h"
#include "RepasChinois.h"

using namespace std;

int main(int argc, char* argv[])
{

	bool src = argc > 2 ? strcmp(argv[1], "src") == 0 : true;
	int testcase = argc> 2 ? atoi(argv[2]) : 14;
	switch (testcase)
	{
	case 1:
	{
		//In this test, we only want to compute the global death stats, focus on this. Not on potential futur behavior
		if (src)
		{
			unsigned long long result = 0;
			Source::Test1 tst(4000);
			for (int i = 0; i < 1000; ++i)
			{
				tst._KillRandom();
				result += tst.ComputeDeathStats();
			}
			//301814810000
			return (int)result;
		}
		else
		{
			unsigned long long result = 0;
			Test::Test1 tst(4000);
			for (int i = 0; i < 1000; ++i)
			{
				tst._KillRandom();
				result += tst.ComputeDeathStats();
			}
			return (int)result;
		}
	}
	case 2:
	{
		if (src)
		{
			Source::Test2 tst;
			for (int i = 0; i < 1000000; ++i)
			{
				Source::Test2::_Mob _mob(i);
				tst.PushMob(_mob);
			}
			for (int i = 0; i < 1000000; ++i)
			{
				tst.PopMob();
			}
			return (int)1;
		}
		else
		{
			Test::Test2 tst;
			for (int i = 0; i < 1000000; ++i)
			{
				Test::Test2::_Mob _mob(i);
				tst.PushMob(_mob);
			}
			for (int i = 0; i < 1000000; ++i)
			{
				tst.PopMob();
			}
			return (int)1;
		}
	}
	case 3:
	{
		if (src)
		{
			//in this test we build kind of dependancy tree of replica objects for network purpose
			//ex : vehicule->player who drive it -> backpack of the player
			//object have an id only unique relative to its parent.
			//and we want to compute a 'composite' id : an Unique ID that represent the object.  
			Source::Test3 t;
			std::vector<Source::Test3::Replica*> filler;
			for (int i = 0; i < 10000; ++i)
			{
				Source::Test3::Replica* r = new Source::Test3::Replica();
				r->Uid = i;
				if (i > 5)
				{
					int index = rand() % filler.size();
					r->depth = filler[index]->depth + 1;
					r->_parent = filler[index];
					r->depth = r->_parent->depth + 1;
					r->_parent->_children.push_back(r);
				}
				else
				{
					r->depth = 0;
					t._PushReplica(r);
				}
				filler.push_back(r);
			}
			int result = 0;
			//this composite ID will be used numerous time across lot of gameplay code 
			for (int i = 0; i < 10000000; ++i)
			{
				result += (int)filler[rand() % filler.size()]->ComputeCompositeID();
			}
			for (auto* r : filler)
			{
				delete r;
			}
			return result;

		}
		else
		{
			Test::Test3 t;
			std::vector<Test::Test3::Replica*> filler;
			for (int i = 0; i < 10000; ++i)
			{
				Test::Test3::Replica* r = new Test::Test3::Replica();
				r->Uid = i;
				if (i > 5)
				{
					int index = rand() % filler.size();
					r->depth = filler[index]->depth + 1;
					r->_parent = filler[index];
					r->depth = r->_parent->depth + 1;
					r->_parent->_children.push_back(r);
				}
				else
				{
					r->depth = 0;
					t._PushReplica(r);
				}
				filler.push_back(r);
			}
			int result = 0;
			for (int i = 0; i < 10000000; ++i)
			{
				result += (int)filler[rand() % filler.size()]->ComputeCompositeID();
			}
			for (auto* r : filler)
			{
				delete r;
			}
			return result;
		}
	}
	case 4:
	{
		if(src)
		{
			Source::Test4 t;
			double result = 0;
			for (int i = 0; i < 10000000; ++i)
			{
				result += t.FractionOfPi((Source::Test4::fracOfPi)(rand() % 6));
			}
			return (int)result;
		}
		else
		{
			Test::Test4 t;
			double result = 0;
			for (int i = 0; i < 10000000; ++i)
			{
				result += t.FractionOfPi((Test::Test4::fracOfPi)(rand() % 6));
			}
			return (int)result;
		}
	}
	case 5:
	{
		int result = 0;
		int rand = std::rand();
		float minHeight = (float) ((rand & 0xFF) % 4) + 3;
		float maxHeight = minHeight + (((rand & 0xFF00) >> 8) % 6);
		if(src)
		{
			for (int i = 0; i < 10000; ++i)
			{
				Source::Test5 t;
				t._CreateForest(200, minHeight, maxHeight);
				for (int i = 0; i < 100; ++i)
				{
					auto& tree = t.FindOneOfTallestTree();
					result += (int)tree.height;
					tree.height = 1; //cut 
				}
			}
		}
		else
		{
			for (int i = 0; i < 10000; ++i)
			{
				Test::Test5 t;
				t._CreateForest(200, minHeight, maxHeight);
				for (int i = 0; i < 100; ++i)
				{
					auto& tree = t.FindOneOfTallestTree();
					result += (int)tree.height;
					tree.height = 1; //cut 
				}
			}
		}
			return result;
	}
	case 6:
	{
		long long result = 0;
		const int S = 2048;
		double A[S];
		double B[S];
		for (int i = 0; i < S; ++i)
		{
			A[i] = (i) / 3.f;
			B[i] = (i) / 2.f;
		}

		if (src)
		{
			Source::Test6 t(1000);
			for (int i = 0; i < 100000; ++i)
			{
				result += t.Increment(rand()% 5, rand()% 5);
			}
		}
		else
		{
			Test::Test6 t(1000);
			for (int i = 0; i < 100000; ++i)
			{
				result += t.Increment(rand()% 5,rand()% 5);
			}
		}
		return (int)result;
	}
	case 7:
	{
		int result = 0;
		if (src)
		{
			Source::Test7 t;
			t._Reserve(100);
			for (int n = 0; n < 10000; ++n)
			{
				for (int i = 0; i < 20; ++i)
				{
					int rand = std::rand();
					t._InsertPlayer(Source::Test7::_Player{ i, rand % 128, rand % 64, rand % 32 });
				}
				result += t.FindSkillestPlayer();
			}
		}
		else
		{
			Test::Test7 t;
			t._Reserve(100);
			for (int n = 0; n < 10000; ++n)
			{
				for (int i = 0; i < 20; ++i)
				{
					int rand = std::rand();
					t._InsertPlayer(Test::Test7::_Player{ i, rand % 128, rand % 64, rand % 32 });
				}
				result += t.FindSkillestPlayer();
			}
		}
		return result;
	}

	case 8:
	{
		int result = 0;
		if (src)
		{
			Source::Test8 t;
			//creating items
			for (int n = 0; n < 1000; ++n)
			{
				t._AddItem(Source::Test8::_Item(std::rand() % 9999));
			}
			//populating players with items
			for (int n = 0; n < 2000; ++n)
			{
				Source::Test8::_Inventory inventory;
				for (int i = 0; i < 20; ++i)
				{
					int id = std::rand() % 9999;
					if (t._IsValidItem(id))
						inventory.AddItem(id);
				}
				t._AddInventory(inventory);
			}
			//function to optimize : this question have multiple layer possible from 'meh' optimisation to 'best' optimisation
			//points will be rewarded depending of this.
			return t.RetrieveMostCommon();
		}
		else
		{
			Test::Test8 t;
			//creating items
			for (int n = 0; n < 1000; ++n)
			{
				t._AddItem(Test::Test8::_Item(std::rand() % 9999));
			}
			//populating players with items
			for (int n = 0; n < 2000; ++n)
			{
				Test::Test8::_Inventory inventory;
				for (int i = 0; i < 20; ++i)
				{
					int id = std::rand() % 9999;
					if (t._IsValidItem(id))
						inventory.AddItem(id);
				}
				t._AddInventory(inventory);
			}
			//function to optimize : this question have multiple layer possible from 'meh' optimisation to 'best' optimisation
			//points will be rewarded depending of this.
			return t.RetrieveMostCommon();
		}
		return result;
	}


	case 21:
	{
		RepasChinois repas;
		repas.MettreLaTable();
		repas.Manger();
		return 1;
	}
	}
	return -1;
}

