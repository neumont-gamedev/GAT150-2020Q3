#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/RenderComponent.h"

namespace nc
{
    bool GameObject::Create(const std::string& name, void* data)
    {
        m_name = name;

        return true;
    }

    void GameObject::Destroy()
    {
        RemoveAllComponents();
    }

    void GameObject::Update()
    {
        for (Component* component : m_components)
        {
            component->Update();
        }
    }

    void GameObject::Draw()
    {
        RenderComponent* component = GetComponent<RenderComponent>();
        if (component)
        {
            component->Draw();
        }
    }

    void GameObject::AddComponent(Component* component)
    {
        assert(std::find(m_components.begin(), m_components.end(), component) == m_components.end());

        component->m_owner = this;
        m_components.push_back(component);
    }

    void GameObject::RemoveComponent(Component* component)
    {
        assert(component);

        auto iter = std::find(m_components.begin(), m_components.end(), component);
        if (iter != m_components.end())
        {
            (*iter)->Destroy();
            delete (*iter);
            m_components.erase(iter);
        }
    }
    void GameObject::RemoveAllComponents()
    {
        for (Component* component : m_components)
        {
            component->Destroy();
            delete component;
        }

        m_components.clear();
    }
}
