#pragma once
#include "Resource.h"
#include <map>

namespace nc
{
	class ResourceManager
	{
	public:
		bool Startup();
		void Shutdown();

		template <typename T>
		T* Get(const std::string& name, void* data)
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

	private:
		std::map<std::string, Resource*> m_resources;
	};
}
