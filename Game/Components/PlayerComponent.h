#pragma once
#include "Components/Component.h"

namespace nc
{
	class PlayerComponent : public Component
	{
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() { return new PlayerComponent(*this); }

		virtual void Update() override;

		//OBJECT_FACTORY_REGISTER_DECLARATION(PlayerComponent)
	};
}

