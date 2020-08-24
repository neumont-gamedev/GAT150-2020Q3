#include "pch.h"
#include "RigidBodyComponent.h"

namespace nc
{
	void RigidBodyComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
	}

	void RigidBodyComponent::Destroy()
	{
	}

	void RigidBodyComponent::Read(const rapidjson::Value& value)
	{
		json::Get(value, "isDynamic", m_isDynamic);
		json::Get(value, "size", m_size);
		json::Get(value, "density", m_density);
		json::Get(value, "friction", m_friction);
		
		m_body = m_owner->m_engine->GetSystem<PhysicsSystem>()->CreateBody(m_owner->m_transform.position, m_size, m_density, m_isDynamic);
	}

	void RigidBodyComponent::Update()
	{
		m_owner->m_transform.position = m_body->GetPosition();
		m_owner->m_transform.angle = m_body->GetAngle();
	}
}
