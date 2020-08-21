#include "pch.h"
#include "ObjectFactory.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"

namespace nc
{
	void ObjectFactoryImpl::Initialize()
	{
		nc::ObjectFactory::Instance().Register("GameObject", new nc::Creator<nc::GameObject, nc::Object>);
		nc::ObjectFactory::Instance().Register("PhysicsComponent", new nc::Creator<nc::PhysicsComponent, nc::Object>);
		nc::ObjectFactory::Instance().Register("SpriteComponent", new nc::Creator<nc::SpriteComponent, nc::Object>);
		nc::ObjectFactory::Instance().Register("SpriteAnimationComponent", new nc::Creator<nc::SpriteAnimationComponent, nc::Object>);
	}
}
