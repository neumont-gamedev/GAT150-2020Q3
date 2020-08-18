#pragma once
#include "Core/Factory.h"
#include "Core/Singleton.h"
#include "Object.h"

#define OBJECT_FACTORY_REGISTER_DECLARATION(classType) \
	static void Register() \
	{ \
		ObjectFactory::Instance().Register(#classType, nc::Object::Instantiate<classType>); \
	}

namespace nc
{
	class ObjectFactoryImpl: public Factory<Object, std::string> 
	{
	public:
		void Initialize();
	};

	class ObjectFactory : public Singleton<ObjectFactoryImpl> {};
}
