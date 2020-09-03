#include "pch.h"
#include "EventManager.h"

namespace nc
{
	void EventManager::Subscribe(const std::string& type, function_t function, Object* owner)
	{
		Observer observer;
<<<<<<< HEAD

=======
>>>>>>> GAT150B
		observer.function = function;
		observer.owner = owner;

		m_observers[type].push_back(observer);
	}

	void EventManager::Notify(const Event& event)
	{
		auto observers = m_observers[event.type];
<<<<<<< HEAD
		for (auto observer : observers)
		{
=======
		for (auto& observer : observers)
		{
			// send to all, send to receiver -> owner
>>>>>>> GAT150B
			if (event.receiver == nullptr || event.receiver == observer.owner)
			{
				observer.function(event);
			}
		}
	}
<<<<<<< HEAD
}
=======
}
>>>>>>> GAT150B
