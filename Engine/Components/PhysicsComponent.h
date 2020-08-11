#pragma once
#include "Component.h"
#include "Math/Vector2.h"

namespace nc
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void Update();

	protected:
		Vector2 m_force;
		Vector2 m_velocity;
	};

}
