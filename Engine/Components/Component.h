#pragma once
#include "Objects/Object.h"

namespace nc
{
	class Component : public Object
	{
	public:
		virtual void Update() = 0;

		friend class GameObject;

	protected:
		class GameObject* m_owner{ nullptr };
	};
}