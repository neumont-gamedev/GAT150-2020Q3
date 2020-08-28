#include "pch.h"
#include "TileMap.h"
#include "Objects/GameObject.h"
#include "Objects/Scene.h"

namespace nc
{
	void TileMap::Read(const rapidjson::Value& value)
	{
		json::Get(value, "numX", m_numX);
		json::Get(value, "numY", m_numY);
		json::Get(value, "size", m_size);
		json::Get(value, "start", m_start);
		json::Get(value, "tileNames", m_tileNames);
		json::Get(value, "tiles", m_tiles);
	}

	void TileMap::Create(Scene* scene)
	{
		for (int i = 0; i < m_tiles.size(); i++)
		{
			int index = m_tiles[i];
			if (m_tiles[i] != 0)
			{
				float x = i % m_numX;
				float y = i / m_numX;
				nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>(m_tileNames[index]);
				gameObject->m_transform.position = m_start + nc::Vector2{ x, y } * m_size;
			
				scene->AddGameObject(gameObject);
			}
		};

	}
}
