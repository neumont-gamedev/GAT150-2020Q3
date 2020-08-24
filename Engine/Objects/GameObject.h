#pragma once
#include "ObjectFactory.h"
#include "Math/Transform.h"
#include "Engine.h"
#include <bitset>

namespace nc
{
	class Component;

	class GameObject : public Object
	{
	public:
		enum eState
		{
			ACTIVE,
			VISIBLE,
			DESTROY,
			TRANSIENT
		};

	public:
		GameObject() = default;
		GameObject(const GameObject& other);

		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() const override { return new GameObject{ *this }; }

		void Read(const rapidjson::Value& value) override;
		void ReadComponents(const rapidjson::Value& value);

		void Update() override;
		void Draw();

		template<typename T>
		T* GetComponent();

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		void RemoveAllComponents();

	public:
		std::string m_name;
		std::string m_tag;
		float m_lifetime;
		
		std::bitset<32> m_flags;

		Transform m_transform;
		Engine* m_engine{ nullptr };



	protected:
		std::vector<Component*> m_components;
	};

	template<typename T>
	T* GameObject::GetComponent()
	{
		T* result{ nullptr };

		for (auto component : m_components)
		{
			result = dynamic_cast<T*>(component);
			if (result) break;
		}

		return result;
	}
}
