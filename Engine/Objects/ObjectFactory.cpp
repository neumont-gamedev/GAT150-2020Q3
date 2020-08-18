#include "pch.h"
#include "ObjectFactory.h"

#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"

namespace nc
{
	void ObjectFactoryImpl::Initialize()
	{
		GameObject::Register();
		PhysicsComponent::Register();
		SpriteComponent::Register();
	}
}
