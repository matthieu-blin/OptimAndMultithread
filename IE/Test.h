#pragma once

#include <set>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <set>
#include <functional>
#include <string>
#include <stack>
#include <sstream> 

//Source code of what you should optimize
//when a class is prefixed by _, you CANNOT modify it.
//when a function or a data member is prefied by a _, you CANNOT modify it.
//Adding function/member/changing type/parameter of a function for a modifiable class is valid
//parameters follow the _ code guideline, BUT can be modified inside a function without _ prefix.
namespace Test
{
	//TEST 11 ////////////////////////////////////////////////////////////////////////
	class Test1
	{
	public:
		struct _Player
		{
			_Player(int _ID) : Uid(_ID) { }
			int Uid = 0;
			unsigned int m_totalDeath = 0;
			bool operator<(const _Player& _player) const {
				return Uid < _player.Uid;
			};
		};

		Test1(int _nb);
		void _KillRandom();
		unsigned long long ComputeDeathStats() const;

	private:

		std::set<_Player> players;
	};

	//TEST 12 ////////////////////////////////////////////////////////////////////////
	class Test2
	{
	public:
		struct _Mob
		{
			_Mob(int _index) {
				life = rand() % 999 + 1;
				archetype = rand() % 5;
				name = _generateName(archetype) + std::to_string(_index);
			}
			unsigned int life = 0;
			int archetype = 0;
			std::string name;
			static const char* _generateName(int archetype)
			{
				switch (archetype)
				{
				case 0: return "super mega power ranger bleu";
				case 1: return "super mega power ranger rouge";
				case 2: return "super mega power ranger vert";
				case 3: return "super mega power ranger jaune";
				case 4: return "super mega power ranger blanc";
				default: return "super mega power ranger noir";
				}
			}

		};

		Test2() {};
		void PushMob(const _Mob _newMob);
		void PopMob();

	private:

		std::stack<_Mob> _mobs;
	};

	//TEST 13 ////////////////////////////////////////////////////////////////////////
	class Test3
	{
	public:

		Test3() {};
		struct Replica
		{
			int Uid = 0;
			int depth = 0;
			Replica* _parent = nullptr;
			std::vector<Replica*> _children;
			long long ComputeCompositeID();
		};

		void _PushReplica(Replica* _entity) { _replicas.push_back(_entity); }

	private:
		std::vector<Replica*> _replicas;

	};

	//TEST 14 ////////////////////////////////////////////////////////////////////////
	class Test4
	{
	public:

		Test4() {};
		enum class fracOfPi
		{
			_2pi,  // 2pi
			_pi,   // pi
			_pi_2, // pi/2
			_pi_4, // pi/4
			_pi_8, // pi/8
			_pi_16 // pi/16
		};
		float _PI = 3.14f;
		float FractionOfPi(fracOfPi p);
	};

	//TEST 15 ////////////////////////////////////////////////////////////////////////
	class Test5
	{
	public:

		Test5() {};
		void _CreateForest(int _nbTrees, float _minHeight, float _maxHeight);
		struct _Tree
		{
			int x = 0;
			int y = 0;
			float height = 1;
		};

		_Tree& FindOneOfTallestTree();


	private:
		_Tree _null{ 0,0, 0 };
		std::vector<_Tree> _forest;
		int _nbTrees = 0;
		float _minHeight = 0;
		float _maxHeight = 0;

	};

	//TEST 16 ////////////////////////////////////////////////////////////////////////
	class Test6
	{
	public:

		Test6(int _n);
		std::vector<int> _valuesA;
		std::vector<int> _valuesB;
		int Increment(int _a, int _b);
	};

	//TEST 17 ////////////////////////////////////////////////////////////////////////
	class Test7
	{
	public:

		Test7() {};
		struct _Player
		{
			int index = 0;
			int skill_1 = 0;
			int skill_2 = 0;
			int skill_3 = 0;
		};


		void _Reserve(size_t _nb) { _players.reserve(_nb); }
		void _InsertPlayer(const _Player& _p) { _players.push_back(_p); }

		int FindSkillestPlayer();


	private:
		std::vector<_Player> _players;

	};

	//TEST 18 ////////////////////////////////////////////////////////////////////////
	class Test8
	{
	public:

		Test8() {};
		using ItemUID = unsigned int;
		struct _Item
		{
			_Item(ItemUID _ID = 0) : Uid(_ID) {
				//we will use uid to look for correct icon, texture, stats, etc.
				std::ostringstream oss;
				oss << "Icon_" << Uid << ".png";
				iconPath = oss.str();
			}
			ItemUID Uid = 0;
			//for simulation of those stats
			std::string iconPath;
		};

		struct _Inventory {

			void AddItem(ItemUID _Uid) { m_inventory.insert(_Uid); }
			const std::set<ItemUID>& Items() const { return m_inventory; }
			std::set<ItemUID> m_inventory;
		};

		void _AddItem(const _Item item) { _items[item.Uid] = item; }
		void _AddInventory(const _Inventory& _inventory) {
			m_playerInventory.push_back(_inventory);
		}

		bool _IsValidItem(ItemUID _Uid) const { return _items.find(_Uid) != _items.end(); }


		//retrieve the most common item possessed by players
		ItemUID  RetrieveMostCommon() const;



	private:
		std::unordered_map< ItemUID, _Item> _items;

		std::list<_Inventory> m_playerInventory;

	};
}