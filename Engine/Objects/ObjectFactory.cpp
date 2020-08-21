#include "pch.h"
#include "ObjectFactory.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"

namespace nc
{
	void ObjectFactoryImpl::Initialize()
	{
		ObjectFactory::Instance().Register("GameObject", new Creator<GameObject, Object>);
		ObjectFactory::Instance().Register("PhysicsComponent", new Creator<PhysicsComponent, Object>);
		ObjectFactory::Instance().Register("SpriteComponent", new Creator<SpriteComponent, Object>);
		ObjectFactory::Instance().Register("SpriteAnimationComponent", new Creator<SpriteAnimationComponent, Object>);
	}
}
