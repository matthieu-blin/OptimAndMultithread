#include "stdafx.h"
#include "Source.h"
#include <algorithm>

namespace Source
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

	void Test0::_GenerateNewPlayer()
	{
		Player player;
		m_players.push_back(player);
	}

//TEST 1 ////////////////////////////////////////////////////////////////////////

	void Test1::FillWithFakeResources(int _nbFake)
	{
		for (int i = 0; i < _nbFake; ++i)
			m_resources.push_back(_Data{ std::rand(), nullptr });
	}

	char* Test1::FindData(long long _guid)
	{
		auto iFound = std::find_if(m_resources.begin(), m_resources.end(),
			[_guid](const _Data& _data)->bool {
			return _data.guid == _guid;
		}
		);
		if (iFound != m_resources.end())
			return iFound->binaryData;
		return nullptr;
	}

//TEST 2 ////////////////////////////////////////////////////////////////////////

	void Test2::InsertPlayer(long long _guid, int _eloScore)
	{
		m_eloPlayers.push_back(_EloPlayer{ _guid, _eloScore });
	}

	long long Test2::FindNearestAdversary(int _eloScore)
	{
		_EloPlayer foundPlayer{-1, -1};
		for (auto& target : m_eloPlayers)
		{
			if (target.eloScore > foundPlayer.eloScore && target.eloScore <= _eloScore + 10)
			{
				foundPlayer = target; 
			}
		}
		return foundPlayer.guid;
	}

//TEST 3 ////////////////////////////////////////////////////////////////////////
	
	void Test3::InsertPosition(const _Vector3& _v)
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
		_Player newPlayer;
		for (const auto& condition : _conditions)
		{
			if (!condition())
				return;
		}
		m_players.push_back(newPlayer);

	}

//TEST 5 ////////////////////////////////////////////////////////////////////////
	std::string Test5::ComputeString(char _letter, const char* _prefix)
	{
		std::string result;
		result = _prefix;
		switch (_letter)
		{
		case 'a' :
			result = result + " alpha"; break;
		case 'b' :
			result = result + " beta"; break;
		case 'c' :
			result = result + " charlie"; break;
		default :
			result = "unimplemented"; break;
		}
		return result;

	}
//TEST 6 ////////////////////////////////////////////////////////////////////////

	void Test6::_InsertXMob(int x)
	{
		for (int i = 0; i < x; ++i)
			m_physicable.push_back(new _Test6Mob());
	}

	void Test6::_InsertXPlayer(int x)
	{
		for (int i = 0; i < x; ++i)
			m_physicable.push_back(new _Test6Player());
	}

	void Test6::ImpulseAll(float _fx, float _fy)
	{
		//first players
		for (auto* p : m_physicable)
		{
			if(p->IsPlayer())
				p->Impulse(_fx, _fy);
		}

		//then mobs
		for (auto* p : m_physicable)
		{
			if(!p->IsPlayer())
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
		for (int i = 0; i < M_SIZE; i++)
			for (int j = 0; j < M_SIZE; j++)
				A[i][j] = std::rand() * 1.f;
	}

	
	void Test8::MultiplyMatrix(const LargeMatrix& A, const LargeMatrix& B, LargeMatrix& R)
	{
		for (int i = 0; i < M_SIZE; i++)
			for (int j = 0; j < M_SIZE; j++)
				for (int k = 0; k < M_SIZE; k++)
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
        _LoadDataSync();
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
			return iData->second->_GetData();
		}
		return nullptr;
    }

 

}//namespace
