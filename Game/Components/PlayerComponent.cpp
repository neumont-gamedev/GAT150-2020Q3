#include "pch.h"
#include "PlayerComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"

namespace nc
{
	void PlayerComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
	}

	void PlayerComponent::Destroy()
	{
	}

	void PlayerComponent::Update()
	{
		auto contacts = m_owner->GetContactsWithTag("Floor");
		bool onGround = !contacts.empty();

		nc::Vector2 force{ 0, 0 };
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			force.x = -100;
		}
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			force.x =  100;
		}

		if (onGround && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
		{
			force.y = -1500;
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			if (audioComponent)
			{
				//audioComponent->SetSoundName("audio/jump.wav");
 				//audioComponent->Play();
			}
		}

		PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(force);

			Vector2 velocity = component->GetVelocity();

			SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
			if (velocity.x <= -0.5f) spriteComponent->Flip();
			if (velocity.x >=  0.5f) spriteComponent->Flip(false);
		}

		// check for coin contact
		auto coinContacts = m_owner->GetContactsWithTag("Coin");
		for (GameObject* contact : coinContacts)
		{
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
			// play sound
		}

		auto enemyContacts = m_owner->GetContactsWithTag("Enemy");
		for (GameObject* contact : enemyContacts)
		{
			// play sound
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			if (audioComponent)
			{
				//audioComponent->SetSoundName("audio/scream.wav");
				//audioComponent->Play();
			}
		}
	}

	void PlayerComponent::CollisionEvent(GameObject* gameObject)
	{
	}
}
