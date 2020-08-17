#pragma once
#include "Core/Factory.h"
#include "Object.h"

namespace nc
{
	class ObjectFactory : public Factory<Object>
	{
	public:
		bool Startup();
		void Shutdown();
	};
}
