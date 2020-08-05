#pragma once
#include <string>

namespace nc
{
	class Resource
	{
	public:
		virtual ~Resource() {}

		virtual bool Create(const std::string& name, void* data) = 0;
		virtual void Destroy() = 0;
	};
}
