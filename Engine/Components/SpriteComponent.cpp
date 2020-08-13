#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace nc
{
	void SpriteComponent::Create(void* data)
	{
		m_texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", m_owner->m_engine->GetSystem<nc::Renderer>());
	}

	void SpriteComponent::Destroy()
	{
	}

	void SpriteComponent::Update()
	{
	}

	void SpriteComponent::Draw()
	{
		m_texture->Draw({ 64, 110, 60, 112 }, m_owner->m_transform.position, { 1, 1 }, m_owner->m_transform.angle);
	}
}
