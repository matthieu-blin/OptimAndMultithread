#include "stdafx.h"
#include "Source.h"
#include <algorithm>
#include <cassert>

namespace Source
{
	//TEST 11 ////////////////////////////////////////////////////////////////////////

	Test1::Test1(int _nb)
	{
		for (int i = 0; i < _nb; ++i)
		{
			players.insert(_Player(i));
		}
	}

	void Test1::_KillRandom() {
		for ( auto& pl : players)
		{
			const_cast<_Player&>(pl).m_totalDeath = rand() % 9999;
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

	void Test2::PushMob(const _Mob _newMob)
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
		if (_parent == nullptr)
		{
			return Uid;
		}
		return Uid + _parent->ComputeCompositeID();
	}

	//TEST 14 ////////////////////////////////////////////////////////////////////////

	float Test4::FractionOfPi(Test4::fracOfPi p)
	{
		switch (p)
		{
		case fracOfPi::_2pi :
			return 2 * _PI;
		case fracOfPi::_pi :
			return  _PI;
		case fracOfPi::_pi_2 :
			return _PI / 2.f;
		case fracOfPi::_pi_4 :
			return _PI / 4.f;
		case fracOfPi::_pi_8 :
			return _PI / 8.f;
		case fracOfPi::_pi_16 :
			return _PI / 16.f;
		default :
			return 0.0f;
		}
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
			_forest.push_back(_Tree{ (rand & 0xFF), ((rand & 0xFF00) >> 8), minHeight + (rand % 11) * 0.1f * (maxHeight - minHeight) });
		}
	}

	Test5::_Tree& Test5::FindOneOfTallestTree()
	{
		_Tree& result = _null;
		for (int i = 0; i < _nbTrees; ++i)
		{
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
		//increase both list with something
		int sum = 0;
		for (int i = 0; i < _valuesA.size(); ++i)
		{
			_valuesA[i] += _a;
			_valuesB[i] += _b;
			sum += _a + _b;
		}
		return sum;

	}


	//TEST 17 ////////////////////////////////////////////////////////////////////////

	int Test7::FindSkillestPlayer()
	{
		int result = 0;
		float sum = 0;
		for (auto& p : _players)
		{
			float _sum = std::sqrtf(p.skill_1 + (p.skill_2 * 2) + (p.skill_3* 3 ));
			if ( sum < _sum )
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
		ItemUID mostcommon = 0;
		unsigned int count = 0;
		for (const auto& inventory : m_playerInventory)
		{
			for (const auto& uid : inventory.Items())
			{
				int currentCount = 0;
				for (const auto& other : m_playerInventory)
				{
					if (&other == &inventory)
						continue;
					for (const auto& ouid : other.Items())
					{
						if (ouid == uid)
							currentCount++;
					}
				}
				if (currentCount >= count)
				{
					if (currentCount > count || uid > mostcommon)
					{
						mostcommon = uid;
						count = currentCount;
					}
				}
			}
		}
		return mostcommon;
	}

}//namespace
