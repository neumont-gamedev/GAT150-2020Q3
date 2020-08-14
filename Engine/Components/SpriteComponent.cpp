#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace nc
{
	void SpriteComponent::Create(void* data)
	{
		m_texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>(m_textureName, m_owner->m_engine->GetSystem<nc::Renderer>());
		ASSERT(m_texture);
	}

	void SpriteComponent::Destroy()
	{
		
	}

	void SpriteComponent::Read(const rapidjson::Value& value)
	{
		nc::json::Get(value, "texture", m_textureName);
		nc::json::Get(value, "rect", m_rect);
	}

	void SpriteComponent::Update()
	{
	}

	void SpriteComponent::Draw()
	{
		m_texture->Draw(m_rect, m_owner->m_transform.position, nc::Vector2{ 1, 1 } * m_owner->m_transform.scale, m_owner->m_transform.angle);
	}
}
