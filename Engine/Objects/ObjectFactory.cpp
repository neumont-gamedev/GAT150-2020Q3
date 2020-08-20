#include "pch.h"
#include "ObjectFactory.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"

namespace nc
{
	void ObjectFactoryImpl::Initialize()
	{
		ObjectFactory::Instance().Register("GameObject", nc::Object::Instantiate<nc::GameObject>);
		ObjectFactory::Instance().Register("PhysicsComponent", nc::Object::Instantiate<nc::PhysicsComponent>);
		ObjectFactory::Instance().Register("SpriteComponent", nc::Object::Instantiate<nc::SpriteComponent>);
		ObjectFactory::Instance().Register("SpriteAnimationComponent", nc::Object::Instantiate<nc::SpriteAnimationComponent>);
	}
}
