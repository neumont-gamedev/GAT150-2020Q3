#pragma once
#include "Core/System.h"
#include <map>
#include <string>
#include <functional>

namespace nc
{
	template <typename TBase, typename TKey>
	class ObjectFactory
	{
	public:
		using function_t = std::function<TBase* ()>;

	public:
		template <typename T = TBase>
		T* Create(TKey key);

		void Register(TKey key, function_t function);

	protected:
		std::map<std::string, function_t> m_registry;

	};

	template<typename TBase, typename TKey>
	template<typename T>
	inline T* ObjectFactory<TBase, TKey>::Create(TKey key)
	{
		T* object{ nullptr };

		auto iter = m_registry.find(key);
		ASSERT_MSG(iter != m_registry.end(), "Could not find " + key + " in the object factory.");
		if (iter != m_registry.end())
		{
			object = dynamic_cast<T*>(iter->second());
		}

		return object;
	}

	template<typename TBase, typename TKey>
	inline void ObjectFactory<TBase, TKey>::Register(TKey key, function_t function)
	{
		m_registry[key] = function;
	}
}