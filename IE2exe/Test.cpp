#include "stdafx.h"
#include "Test.h"

namespace Test
{

//TEST 0 ////////////////////////////////////////////////////////////////////////

	Test0::Player::Player()
	{
		name = (char*)malloc(sizeof(char) * 10);
		for (int i = 0; i < 9; ++i)
			name[i] = ((float)std::rand() / RAND_MAX) * 26.f + 97; //generate rubbish char 
		name[9] = '\0';
	}

	Test0::Player::Player(const Player& _player)
	{
		name = (char*)malloc(sizeof(char) * 10);
		memcpy(name, _player.name, sizeof(_player.name));
		life = _player.life;
	}

	Test0::Player::~Player()
	{
		free(name);
		life = 0;
	}
	//Solution : use move operator instead of copy
	//will avoid the malloc and memcpy cost
	//note : the every operator must exist when declaring a move operator
	//so the copy operator must exist 
	//it will still be used for assignment of temporary var on push back
	Test0::Player::Player(Player&& _player)
	{
		name = _player.name;
		_player.name = nullptr;
		life = _player.life;
	}

	void Test0::_GenerateNewPlayer()
	{
		Player player;
		m_players.push_back(player);
	}

//TEST 1 ////////////////////////////////////////////////////////////////////////

	void Test1::FillWithFakeResources(int _nbFake)
	{
		for (int i = 0; i < _nbFake; ++i)
		{
			long long guid = std::rand();
			m_resources[guid] = _Data{ guid, nullptr };
		}
	}

	char* Test1::FindData(long long _guid)
	{
		auto iFound = m_resources.find(_guid);
		if (iFound != m_resources.end())
			return iFound->second.binaryData;
		return nullptr;
	}


//TEST 2 ////////////////////////////////////////////////////////////////////////

	void Test2::InsertPlayer(long long _guid, int _eloScore)
	{
		m_eloPlayers.insert(_EloPlayer{ _guid, _eloScore });
		
	}

	long long Test2::FindNearestAdversary(int _eloScore)
	{
		for (auto& eloPlayer : m_eloPlayers)
		{
			if (eloPlayer.eloScore <= _eloScore + 10)
			{
				continue;
			}
			return eloPlayer.guid;
		}
		return -1;
	}


//TEST 3 ////////////////////////////////////////////////////////////////////////
	void Test3::InsertPosition(_Vector3 _v)
	{
		m_positions.push_back(_v);
	}


//TEST 4 ////////////////////////////////////////////////////////////////////////
	Test4::_Player::_Player()
	{
		name = (char*)malloc(sizeof(char) * 10);
		for (int i = 0; i < 9; ++i)
			name[i] = ((float)std::rand() / RAND_MAX) * 26.f + 97; //generate rubbish char 
		name[9] = '\0';
	}

	Test4::_Player::_Player(const _Player& _player)
	{
		name = (char*)malloc(sizeof(char) * 10);
		memcpy(name, _player.name, sizeof(_player.name));
		life = _player.life;
	}

	Test4::_Player::~_Player()
	{
		free(name);
	}

	void Test4::InsertNewPlayerAtConditions(const std::vector<std::function<bool()>>& _conditions)
	{
		for (const auto& condition : _conditions)
		{
			if (!condition())
				return;
		}
		m_players.push_back(_Player());

	}

//TEST 5 ////////////////////////////////////////////////////////////////////////
	std::string Test5::ComputeString(char _letter, const char* _prefix)
	{
		static  std::string _str;
		_str = _prefix;
		switch (_letter)
		{
		case 'a' :
			return _str += " alpha";
		case 'b' :
			return _str += " beta";
		case 'c' :
			return _str += " charlie";
		default :
			return  "unimplemented";
		}
		return "" ;

	}

//TEST 6 ////////////////////////////////////////////////////////////////////////

	void Test6::_InsertXMob(int x)
	{
		for (int i = 0; i < x; ++i)
			m_mobs.push_back(new _Test6Mob());
	}

	void Test6::_InsertXPlayer(int x)
	{
		for (int i = 0; i < x; ++i)
			m_players.push_back(new _Test6Player());
	}

	void Test6::ImpulseAll(float _fx, float _fy)
	{
		//first players
		for (auto* p : m_players)
		{
			p->Impulse(_fx, _fy);
		}

		//then mobs
		for (auto* p : m_mobs)
		{
			p->Impulse(_fx, _fy);
		}
	}

//TEST 7 ////////////////////////////////////////////////////////////////////////
	Test7::Entity::Entity(_Component** _components, int _nb)
	{
		m_components = std::vector<_Component*>(_components, _components + _nb);
	}

	void Test7::_InsertXEntity(int x)
	{
		for (int i = 0; i < x; ++i)
		{
			_Component* defaultComponents[] = { new _MeshRender(), new _Transform(), new _GUID() };
			m_entities.push_back(new Entity(defaultComponents, 3));
		}
	}

	void Test7::MoveAllEntities(int x, int y)
	{
		for (auto* entity : m_entities)
		{
			auto* t = entity->GetComponentT<_Transform>(_ComponentType::Transform);
			t->Move(x, y);
		}
	}

//TEST 8 ////////////////////////////////////////////////////////////////////////

	void Test8::_RandMatrix(LargeMatrix& A)
	{
		for (int j = 0; j < M_SIZE; j++)
			for (int i = 0; i < M_SIZE; i++)
				A[i][j] = std::rand() * 1.f;
	}

	
	void Test8::MultiplyMatrix(const LargeMatrix& A, const LargeMatrix& B, LargeMatrix& R)
	{
		for (int i = 0; i < M_SIZE; i++)
			for (int k = 0; k < M_SIZE; k++)
				for (int j = 0; j < M_SIZE; j++)
					R[i][j] += A[i][k] * B[k][j];
	}

//TEST 9 ////////////////////////////////////////////////////////////////////////
	void Test9::_InitializeRandomValue()
	{
		m_randomValues.resize(256);
		for (int i = 0; i < 256; ++i)
		{
			unsigned char value = std::rand() %  256;
			while (std::find(m_randomValues.begin(), m_randomValues.begin() + i, value) !=  m_randomValues.begin() + i )
				value++;
			m_randomValues[i]=value;
		}
	}

	unsigned char Test9::FindNearestRandom(unsigned char _value)
	{
		unsigned char currentGap = 255;
		unsigned char nearest = 255;
		
		for (unsigned char v : m_randomValues)
		{
			if (v == _value)
				return v;
			auto gap = std::abs(_value - v);
			if(gap < currentGap);
			{
				currentGap = gap;
				nearest = v;
			}
		}
		return nearest;
	}

//TEST 10 ////////////////////////////////////////////////////////////////////////

    Test10::IOResource::IOResource(const char* _path)
    {
		uid = _Hash(_path);
    }
    
    void Test10::IOResource::_LoadDataSync()
    {
        //fake code
        unsigned int size = std::rand() % 32384 ;
        data = (char*)malloc(size);
        for (auto i = 0; i < size; ++i)
        {
            data[i] = std::rand() % 255;
        }
    }

    Test10::IOResource::~IOResource()
    {
        free(data);
    }
	
	char* Test10::IOResource::LoadAndGetData()
	{
		if (data == nullptr)
			_LoadDataSync();
		return data;
	}

	unsigned long Test10::IOResource::_Hash(const char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }

    void Test10::_InitResource(const char** paths, int _nb)
    {
        for (int i = 0; i < _nb; ++i)
        {
			auto* data = new IOResource(paths[i]);
			m_data[data->_UID()] = data;
        }
    }

    char* Test10::GetData(const char* _path)
    {
		auto iData = m_data.find(IOResource::_Hash(_path));
		if (iData != m_data.end())
		{
			return iData->second->LoadAndGetData();
		}
		return nullptr;
    }
}//namespace
