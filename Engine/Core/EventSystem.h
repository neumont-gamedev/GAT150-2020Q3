#pragma once
#include "Singleton.h"
#include "Objects/Object.h"
#include <string>
#include <list>
#include <map>
#include <functional>

namespace nc
{
	struct Event
	{
		std::string type;
		Object* sender;
		void* data;
	};

	class EventSystem : public Singleton<EventSystem>
	{
	public:
		using function_t = std::function<void(const Event&)>;
		using handle_t = size_t;

		struct Observer
		{
			function_t function;
			handle_t handle;

			bool operator == (const Observer& other) const
			{
				return handle == other.handle;
			}
		};

	public:
		handle_t Subscribe(const std::string& id, function_t function);
		void Unsubscribe(const handle_t& handle);

		void Notify(const Event& event);

	private:
		EventSystem() {}

	private:
		std::map<std::string, std::list<Observer>> m_observers;
		static size_t ms_handle;
	};
}
