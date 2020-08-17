#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/PlayerComponent.h"
#include "Core/Json.h"
#include "Core/Factory.h"

nc::Engine engine;
nc::Factory<nc::Object, std::string> objectFactory;

int main(int, char**)
{
	engine.Startup();

	objectFactory.Register("GameObject", nc::Object::Instantiate<nc::GameObject>);
	objectFactory.Register("PhysicsComponent", nc::Object::Instantiate<nc::PhysicsComponent>);
	objectFactory.Register("SpriteComponent", nc::Object::Instantiate<nc::SpriteComponent>);
	objectFactory.Register("PlayerComponent", nc::Object::Instantiate<nc::PlayerComponent>);

	nc::GameObject* player = objectFactory.Create<nc::GameObject>("GameObject");

	player->Create(&engine);

	rapidjson::Document document;
	nc::json::Load("player.txt", document);
	player->Read(document);

	nc::Component* component;
	component = objectFactory.Create<nc::Component>("PhysicsComponent");
	player->AddComponent(component);
	component->Create();

	component = objectFactory.Create<nc::Component>("SpriteComponent");
	player->AddComponent(component);
	nc::json::Load("sprite.txt", document);
	component->Read(document);
	component->Create();

	component = objectFactory.Create<nc::Component>("PlayerComponent");
	player->AddComponent(component);
	component->Create();

	nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		// update
		engine.Update();
		player->Update();

		quit = (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED);

		// draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();

		background->Draw({ 0, 0 });
		player->Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	engine.Shutdown();

	return 0;
}

