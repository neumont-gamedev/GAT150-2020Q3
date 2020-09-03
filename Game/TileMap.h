#pragma once
#include "Core/Json.h"
#include "Math/Vector2.h"
#include <vector>

namespace nc
{
<<<<<<< HEAD
=======
	class Scene;

>>>>>>> GAT150B
	class TileMap
	{
	public:
		void Read(const rapidjson::Value& value);
<<<<<<< HEAD
		bool Create(class Scene* scene);

=======
		bool Create(Scene* scene);
	
>>>>>>> GAT150B
	protected:
		int m_numX{ 0 };
		int m_numY{ 0 };
		Vector2 m_size;
		Vector2 m_start;
<<<<<<< HEAD
=======

>>>>>>> GAT150B
		std::vector<std::string> m_tileNames;
		std::vector<int> m_tiles;
	};
}