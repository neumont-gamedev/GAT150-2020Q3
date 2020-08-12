#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace nc
{
    bool SpriteComponent::Create(void* data)
    {
        m_texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", m_owner->m_engine->GetSystem<nc::Renderer>());

        return true;
    }

    void SpriteComponent::Destroy()
    {
    }

    void SpriteComponent::Update()
    {
    }

    void SpriteComponent::Draw()
    {
        m_texture->Draw({ 128, 120, 48, 98 }, m_owner->m_transform.position, { m_owner->m_transform.scale, m_owner->m_transform.scale }, m_owner->m_transform.angle);
    }
}
