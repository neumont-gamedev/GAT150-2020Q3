#include "pch.h"
#include "EventSystem.h"

namespace nc
{
	size_t nc::EventSystem::ms_handle = 0;

	EventSystem::handle_t EventSystem::Subscribe(const std::string& id, function_t function)
	{
		Observer observer;
		observer.function = function;
		observer.handle = ms_handle++;

		m_observers[id].push_back(observer);

		return observer.handle;
	}

	void EventSystem::Unsubscribe(const handle_t& handle)
	{
		for (auto& observers : m_observers)
		{
			for (auto& observer : observers.second)
			{
				if (observer.handle == handle)
				{
					observers.second.remove(observer);
					break;
				}
			}
		}
	}

	void EventSystem::Notify(const Event& event)
	{
		auto iter = m_observers.find(event.type);
		if (iter != m_observers.end())
		{
			auto& observers = iter->second;
			for (auto& observer : observers)
			{
				observer.function(event);
			}
		}
	}
}
