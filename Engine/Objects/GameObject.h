#pragma once
#include "Object.h"
#include "Math/Transform.h"

namespace nc
{
	class Component;

	class GameObject : public Object
	{
	public:
		bool Create(const std::string& name = "", void* data = nullptr) override;
		void Destroy() override;

		void Update();
		void Draw();

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		void RemoveAllComponents();

		template <typename T>
		T* GetComponent()
		{
			T* result = nullptr;
			for (Component* component : m_components)
			{
				result = dynamic_cast<T*>(component);
				if (result != nullptr) break;
			}

			return result;
		}

		Transform& GetTransform() { return m_transform; }

	protected:
		Transform m_transform;
		std::vector<Component*> m_components;
	};
}
