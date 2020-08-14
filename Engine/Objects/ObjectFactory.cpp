#include "pch.h"
#include "ObjectFactory.h"
#include "Components/SpriteComponent.h"


namespace nc
{
    bool ObjectFactory::Startup()
    {
        Register("sprite_component", new Creator<SpriteComponent, Object>());

        //Object* component = Create("sprite_component");

        return true;
    }

    void ObjectFactory::Shutdown()
    {
    }
}
