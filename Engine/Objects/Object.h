#pragma once
#include <string>

namespace nc
{
	class Object
	{
	public:
		virtual bool Create(const std::string& name = "", void* data = nullptr) = 0;
		virtual void Destroy() = 0;

		const std::string& GetName() { return m_name; }

	protected:
		std::string m_name;
	};
}
