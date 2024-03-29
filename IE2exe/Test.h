#pragma once

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <set>
#include <functional>
#include <string>

//Source code of what you should optimize
namespace Test
{
//TEST 0 ////////////////////////////////////////////////////////////////////////
	class Test0
	{
	public :
		class Player
		{
		public:
			Player();
			Player(const Player& _player);
			Player(Player&& _player);
			~Player();
		private :
			char* name = nullptr;
			int life = 0;
		};

		//this function could be call X times
		void _GenerateNewPlayer();
	private :
		std::vector<Player> m_players;
	};


//TEST 1 ////////////////////////////////////////////////////////////////////////
	class Test1
	{
	public:
		struct _Data
		{
			long long guid;
			char* binaryData;
		};
		void FillWithFakeResources(int _nbFake);
		char* FindData(long long _guid);

	private :
		//solution : since we want to load all at once, then Finding Data N times
		//the hashmap with its O(1) access in reading is most appropriate
		std::unordered_map<long long , _Data> m_resources;
	};

//TEST 2 ////////////////////////////////////////////////////////////////////////

	class Test2
	{
	public:
		struct _EloPlayer
		{
			long long guid;
			int eloScore;
			friend  bool operator<(const _EloPlayer& l, const _EloPlayer& r)
			{
				return l.eloScore < r.eloScore;
			}
		};


		void InsertPlayer(long long _guid, int _eloScore );
		//find the a player with a elo score < to our score +10 max
		long long FindNearestAdversary(	int _eloScore);

	private :
		std::set<_EloPlayer> m_eloPlayers;
	};

//TEST 3 ////////////////////////////////////////////////////////////////////////
	class Test3
	{
	public:
		struct _Vector3
		{
			float x;
			float y;
			float z;
		};

		void InsertPosition(_Vector3 _v);

	private :
		std::vector<_Vector3> m_positions;
	};


//TEST 4 ////////////////////////////////////////////////////////////////////////
	class Test4
	{
	public:
		struct _Player
		{
			_Player();
			_Player(const _Player& _player);
			~_Player();
			char* name = nullptr;
			int life = 100;
		};

		void InsertNewPlayerAtConditions(const std::vector<std::function<bool()>>& _conditions);
	private:
		std::vector<_Player> m_players;
	};

//TEST 6 ////////////////////////////////////////////////////////////////////////

	class _Test6PhysicableI
	{
	public:
		virtual void Impulse(float _fx, float _fy) = 0;
		virtual bool IsPlayer() = 0;
	protected:
		float m_X = 0.f;
		float m_Y = 0.f;
	};
	class _Test6Player : public _Test6PhysicableI
	{
	public:
		virtual bool IsPlayer() { return true; }
		void Impulse(float _x, float _y) override
		{
			m_X += _x;
			m_Y += _y;
		}
	};

	class _Test6Mob : public _Test6PhysicableI
	{
	public : 
		virtual bool IsPlayer() { return false; }
		//impulse reversed for no reason and we dont care
		void Impulse(float _x, float _y) override
		{
			m_X -= _x;
			m_Y -= _y;
		}
	};	class Test6
	{
	public:
		void InsertXMob(int x);
		void InsertXPlayer(int x);
		void ImpulseAll(float _fx, float _fy);

	private :

		std::vector<_Test6Mob*> m_mobs;
		std::vector<_Test6Player*> m_players;
	};


	//TEST 6b ////////////////////////////////////////////////////////////////////////

	class _Test6bPlayer
	{
	public:
		void Impulse(float _x, float _y) 
		{
			m_X += _x;
			m_Y += _y;
		}
	private:
		float m_X = 0.f;
		float m_Y = 0.f;
	};

	class _Test6bMob 
	{
	public:
		//impulse reversed for no reason and we dont care
		void Impulse(float _x, float _y) 
		{
			m_X -= _x;
			m_Y -= _y;
		}
	private:
		float m_X = 0.f;
		float m_Y = 0.f;
	};	
	class Test6b
	{
	public:
		void InsertXMob(int x);
		void InsertXPlayer(int x);
		void ImpulseAll(float _fx, float _fy);

	private:

		std::vector<_Test6bMob*> m_mobs;
		std::vector<_Test6bPlayer*> m_players;
	};

	//TEST 7 ////////////////////////////////////////////////////////////////////////
	class Test7
	{
		enum class _ComponentType{
			Transform = 0,
			MeshRenderer,
			GUID,
		};
		class _Component
		{
		public :
			_Component(_ComponentType type) : m_type(type) {};
			_ComponentType GetType() const { return m_type; }
		private :
			_ComponentType m_type;
		};
		class _Transform : public _Component
		{
		public : 
			_Transform() : _Component(_ComponentType::Transform) {
				x = std::rand();
				y = std::rand();
			}
			void Move(int _x, int _y) { x = _x; y = _y; }
		private :
			int x;
			int y;
		};
		class _MeshRender : public _Component
		{
		public :
			_MeshRender() : _Component(_ComponentType::MeshRenderer) {
				meshPath = "dummyFolder" + std::to_string(std::rand());
			}
			std::string meshPath;
		};
		class _GUID : public _Component
		{
		public :
			_GUID() : _Component(_ComponentType::GUID) { guid = std::rand(); }
			int guid;
		};
		class Entity
		{
		public:
			Entity(_Component** _components, int _nb);
			template <typename T>
			T* GetComponentT(_ComponentType _type)
			{
				return static_cast<T*>(GetComponent(_type));

			}
			_Component* GetComponent(_ComponentType _type)
			{
				for (auto* comp : m_components)
				{
					if (comp->GetType() == _type)
						return comp;
				}
				return nullptr;
			}
			template<> 
			_Transform* GetComponentT(_ComponentType _type) {
				if (!m_transform)
					m_transform = static_cast<_Transform*>(GetComponent(_type));
				return m_transform;
			}

		private :
			std::vector<_Component*> m_components;
			_Transform* m_transform = nullptr;
		};
	public:
		void _InsertXEntity(int x);
		void MoveAllEntities(int x, int y);

	private :
		std::vector<Entity*> m_entities;
	};

//TEST 8 ////////////////////////////////////////////////////////////////////////
	class Test8
	{
	public:
#if _DEBUG
		static const int M_SIZE = 128;
#else
		static const int M_SIZE = 256;
#endif
		typedef float LargeMatrix[M_SIZE][M_SIZE];
		static void _RandMatrix(LargeMatrix& A);
		static void MultiplyMatrix(const LargeMatrix& A, const LargeMatrix& B, LargeMatrix& R);

	};

	
//TEST 9 ////////////////////////////////////////////////////////////////////////
	class Test9
	{
	public :
		void _InitializeRandomValue();
		unsigned char  FindNearestRandom(unsigned char _value);
	private :
		std::vector<unsigned char> m_randomValues;
	};

//TEST 10 ////////////////////////////////////////////////////////////////////////
	class Test10
	{
	public :
		class IOResource
		{
        public:
			IOResource(const char* _path);
            ~IOResource();

			unsigned long _UID() const { return uid; }
			char* _GetData() const { return data; }
			char* LoadAndGetData();
            static unsigned long _Hash(const char *str);

		private:
			void _LoadDataSync();
			unsigned long uid;
            char* data = nullptr;
            
		};

        void _InitResource(const char** paths, int _nb);
        char* GetData(const char* _path);
	private :

		std::unordered_map<unsigned long long, IOResource*> m_data;
	};

	//TEST 11 ////////////////////////////////////////////////////////////////////////
	class Test11
	{
	public:
		int SumAllDigits(const char* _text);
	};

	//TEST 12 ////////////////////////////////////////////////////////////////////////
	class Test12
	{
	public:
		unsigned long filterArray(unsigned long* _pArray, unsigned long _size);
	}; 

	
}