#include "pch.h"
#include "PhysicsSystem.h"

namespace nc
{
    bool PhysicsSystem::Startup()
    {
        b2Vec2 gravity{ 0, -10 };
        m_world = new b2World{ gravity };

        return true;
    }

    void PhysicsSystem::Shutdown()
    {
        delete m_world;
        m_world = nullptr;
    }

    void PhysicsSystem::Update()
    {
        float timeStep = 1.0f / 60.0f;
        m_world->Step(timeStep, 8, 3);
    }

    b2Body* PhysicsSystem::CreateBody(const Vector2& position, const Vector2& size, float density, bool isDynamic)
    {
        b2BodyDef bodyDef;

        bodyDef.type = (isDynamic) ? b2_dynamicBody : b2_staticBody;
        bodyDef.position.Set(position.x, position.y);
        b2Body* body = m_world->CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(size.x, size.y);

        body->CreateFixture(&shape, density);

        return body;
    }
}
