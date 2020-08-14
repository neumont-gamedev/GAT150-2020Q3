#pragma once
#include "Singleton.h"
#include <string>
#include <map>

namespace nc
{
	template<typename TBase>
	class CreatorBase
	{
	public:
		virtual TBase* Create() const = 0;
	};

	template<typename T, typename TBase>
	class Creator : public CreatorBase<TBase>
	{
	public:
		virtual TBase* Create() const override { return new T; }
	};

	template<typename TBase, typename TKey = std::string>
	class Factory : public Singleton<Factory<TBase, TKey>>
	{
	public:
		~Factory();

		template<typename T = TBase>
		T* Create(TKey key);

		void Register(TKey key, CreatorBase<TBase>* creator);

	private:
		std::map<TKey, CreatorBase<TBase>*> m_registry;
	};

	template<typename TBase, typename TKey>
	inline Factory<TBase, TKey>::~Factory()
	{
		for (const auto& iter : m_registry)
		{
			delete iter.second;
		}

		m_registry.clear();
	}

	template<typename TBase, typename TKey>
	template<typename T>
	inline T* Factory<TBase, TKey>::Create(TKey key)
	{
		auto iter = m_registry.find(key);
		if (iter == m_registry.end())
		{
			return nullptr;
		}

		CreatorBase<TBase>* creator = (*iter).second;

		return dynamic_cast<T*>(creator->Create());
	}

	template<typename TBase, typename TKey>
	inline void Factory<TBase, TKey>::Register(TKey key, CreatorBase<TBase>* creator)
	{
		if (m_registry.find(key) == m_registry.end())
		{
			m_registry[key] = creator;
		}
	}
}
