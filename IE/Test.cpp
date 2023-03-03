#include "stdafx.h"
#include "Test.h"

namespace Test
{

	//TEST 11 ////////////////////////////////////////////////////////////////////////
 
	Test1::Test1(int _nb)
	{
		//on evite les reallocs puisqu'on connait cette fois le N
		players.reserve(_nb);
		for (int i = 0; i < _nb; ++i)
		{
			players.push_back(_Player(i));
		}
	}


	void Test1::_KillRandom() {
		for (auto& pl : players)
		{
			pl.m_totalDeath = rand() % 9999;
		}
	}

	unsigned long long Test1::ComputeDeathStats() const
	{
		unsigned long long result = 0;
		for (const auto& pl : players)
		{
			result += pl.m_totalDeath;
		}
		return result;
	}

	//TEST 12 ////////////////////////////////////////////////////////////////////////

	void Test2::PushMob(const _Mob& _newMob)
	{
		_mobs.push(_newMob);
	}

	void Test2::PopMob()
	{
		_mobs.pop();
	}


	//TEST 13 ////////////////////////////////////////////////////////////////////////

	long long Test3::Replica::ComputeCompositeID()
	{
		//la recursion multiplie les call de fonctions et n'est pas très cache friendly
		long long result = Uid;
		Replica* p = _parent;
		for (int i = 0; i < depth; ++i)
		{
			result += p->Uid;
			p = p->_parent;
		}
		return result;
	}


	//TEST 14 ////////////////////////////////////////////////////////////////////////

	float Test4::FractionOfPi(Test4::fracOfPi p)
	{
		//un cache vaut mieux que de faire les calculs à répétition
		return frac[(int)p];
	}

	//TEST 15 ////////////////////////////////////////////////////////////////////////

	void Test5::_CreateForest(int nbTrees, float minHeight, float maxHeight)
	{
		_nbTrees = nbTrees;
		_forest.reserve(_nbTrees);
		_minHeight = minHeight;
		_maxHeight = maxHeight;


		for (int i = 0; i < _nbTrees; ++i)
		{
			int rand = std::rand();
			_forest.push_back(_Tree{ (rand & 0xFF), ((rand & 0xFF00)>>8), minHeight + (rand % 11) * 0.1f * (maxHeight - minHeight) });
		}
	}

	Test5::_Tree& Test5::FindOneOfTallestTree()
	{
		_Tree& result = _null;
		for (int i = 0; i < _nbTrees; ++i)
		{
			//on oublie pas de quitter si on trouve une solution potentielle !
			//on réduit ainsi notre theta()
			if (_forest[i].height == _maxHeight)
			{
				return _forest[i];
			}
			if (result.height < _forest[i].height)
			{
				result = _forest[i];
			}
		}
		return result;
	}

	//TEST 16 ////////////////////////////////////////////////////////////////////////

	Test6::Test6(int _n)
	{
		_valuesA.resize(_n);
		_valuesB.resize(_n);
	}
	int Test6::Increment(int _a, int _b)
	{
		int sum = 0;
		//ça prend plus de place en écriture, mais on utilise mieux le cache cpu
		for (auto& v : _valuesA)
		{
			v += _a;
			sum += _a;
		}
		for (auto& v : _valuesB)
		{
			v += _b;
			sum += _b;
		}
		return sum;
	}




	//TEST 17 ////////////////////////////////////////////////////////////////////////

	int Test7::FindSkillestPlayer()
	{
		int result = 0;
		long long sum = 0;
		for (auto& p : _players)
		{
			//il ne faut pas oublier que les mathématiques peuvent nous aider à simplifier le problème 
			//avec moins d'opération couteuse pour le même résultat
			auto  _sum = p.skill_1 + p.skill_2 * 2   + p.skill_3 * 3 ;
			if (sum < _sum)
			{
				result = p.index;
				sum = _sum;
			}
		}
		return result;
	}

	//TEST 18 ////////////////////////////////////////////////////////////////////////

//retrieve the most common item possessed by players

	Test8::ItemUID Test8::RetrieveMostCommon() const {
		//etablissons d'abord le nombre d'item
		std::unordered_map<ItemUID, unsigned int> itemCounter;
		for (const auto& inventory : m_playerInventory)
			for (const auto& uid : inventory.Items())
				itemCounter[uid]++;

		//faisons une recherche ensuite en O(n)
		ItemUID mostCommon = -1;
		unsigned int maxCount = 0;
		for (auto& itemCountEntry : itemCounter)
		{
			if (itemCountEntry.second > maxCount)
			{
				maxCount = itemCountEntry.second;
				mostCommon = itemCountEntry.first;
			}
		}
		return mostCommon;
	}

}//namespace
