#pragma once
#include "Resource.h"
#include "Object/System.h"
#include <map>

namespace nc
{
	class ResourceManager : public System
	{
	public:
		bool Startup();
		void Shutdown();
		void Update();

		template <typename T>
		T* Get(const std::string& name, void* data);

		void Remove(const std::string& name);
		void RemoveAll();

	private:
		std::map<std::string, Resource*> m_resources;
	};

	template<typename T>
	inline T* ResourceManager::Get(const std::string& name, void* data)
	{
		T* resource = dynamic_cast<T*>(m_resources[name]);

		if (resource == nullptr)
		{
			resource = new T;
			resource->Create(name, data);

			m_resources[name] = resource;
		}

		return resource;
	}
}
