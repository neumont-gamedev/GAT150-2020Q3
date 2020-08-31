#include "pch.h"
#include "TileMap.h"
#include "Objects/ObjectFactory.h"
#include "Objects/GameObject.h"
#include "Objects/Scene.h"

void nc::TileMap::Read(const rapidjson::Value& value)
{
    json::Get(value, "numX", m_numX);
    json::Get(value, "numY", m_numY);
    json::Get(value, "size", m_size);
    json::Get(value, "start", m_start);

    json::Get(value, "tileNames", m_tileNames);
    json::Get(value, "tiles", m_tiles);
}

bool nc::TileMap::Create(Scene* scene)
{
    for (size_t i = 0; i < m_tiles.size(); i++)
    {
        int index = m_tiles[i];
        if (index != 0)
        {
            GameObject* gameObject = ObjectFactory::Instance().Create<GameObject>(m_tileNames[index]);

            // i = 0, 1, 2, 3, 4, 5, 6, 7, 8
            //     0, 1, 2, 3, 4
            //     0, 1, 2, 3, 4
            float x = static_cast<float>(i % m_numX);

            // i = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
            //     0, 0, 0, 0, 0
            //     1, 1, 1, 1, 1

            float y = static_cast<float>(i / m_numX);
            gameObject->m_transform.position = m_start + (nc::Vector2{ x, y } * m_size);

            scene->AddGameObject(gameObject);
        }
    }


    return true;
}
