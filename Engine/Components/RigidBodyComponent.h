#pragma once
#include "PhysicsComponent.h"
#include "box2d/box2d.h"

namespace nc
{
	class RigidBodyComponent : public PhysicsComponent
	{
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() const override { return new RigidBodyComponent{ *this }; }

		void Read(const rapidjson::Value& value) override;

		virtual void Update() override;

	protected:
		bool m_isDynamic{ false };
		Vector2 m_size;
		float m_density{ 1 };
		float m_friction{ 1 };

		b2Body* m_body{ nullptr };
	};
}