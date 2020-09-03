#include "pch.h"
#include "EnemyComponent.h"
#include "Components/PhysicsComponent.h"
<<<<<<< HEAD
#include "Objects/GameObject.h"
#include "Objects/Scene.h"
=======
>>>>>>> GAT150B

namespace nc
{
	void EnemyComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
	}

	void EnemyComponent::Destroy()
	{
	}

	void EnemyComponent::Update()
	{
		GameObject* player = m_owner->m_scene->Find("Player");
		if (player)
		{
			Vector2 direction = player->m_transform.position - m_owner->m_transform.position;
<<<<<<< HEAD
			Vector2 force = direction.Normalized() * 5.0f;
=======
			Vector2 force = direction.Normalized() * 10.0f;
>>>>>>> GAT150B

			PhysicsComponent* physicsComponent = m_owner->GetComponent<PhysicsComponent>();
			physicsComponent->ApplyForce(force);
		}
	}
<<<<<<< HEAD

}

=======
}
>>>>>>> GAT150B
