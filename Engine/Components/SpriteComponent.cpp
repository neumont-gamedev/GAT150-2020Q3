#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace nc
{
	void SpriteComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);

		//ASSERT_MSG((m_texture != nullptr), "Error texture " + m_textureName + " not loaded.");
	}

	void SpriteComponent::Destroy()
	{
	}

	void SpriteComponent::Read(const rapidjson::Value& value)
	{
		json::Get(value, "texture", m_textureName);
		json::Get(value, "rect", m_rect);
	}

	void SpriteComponent::Update()
	{
	}

	void SpriteComponent::Draw()
	{
		Texture* texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>(m_textureName, m_owner->m_engine->GetSystem<nc::Renderer>());
		texture->Draw(m_rect, m_owner->m_transform.position, Vector2::one * m_owner->m_transform.scale, m_owner->m_transform.angle);
	}
}
