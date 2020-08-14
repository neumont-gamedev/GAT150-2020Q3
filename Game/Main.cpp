#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Core/Json.h"

nc::Engine engine;
nc::GameObject player;

int main(int, char**)
{
	rapidjson::Document document;

	engine.Startup();

	player.Create(&engine);
	nc::json::Load("players.txt", document);
	player.Read(document);

	nc::Component* component;
	component = new nc::PhysicsComponent;
	player.AddComponent(component);
	component->Create();

	component = new nc::SpriteComponent;
	player.AddComponent(component);
	nc::json::Load("sprite.txt", document);
	component->Read(document);
	component->Create();

	nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());

	nc::Vector2 velocity{ 0, 0 };

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
		player.Update();

		quit = (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED);

		// player controller
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			player.m_transform.angle = player.m_transform.angle - 200.0f * engine.GetTimer().DeltaTime();
		}
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			player.m_transform.angle = player.m_transform.angle + 200.0f * engine.GetTimer().DeltaTime();
		}

		nc::Vector2 force{ 0, 0 };
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2::forward * 1000.0f;
		}
		force = nc::Vector2::Rotate(force, nc::DegreesToRadians(player.m_transform.angle));

		// draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();

		background->Draw({ 0, 0 });
		player.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	engine.Shutdown();

	return 0;
}

//rapidjson::Document document;
//nc::json::Load("json.txt", document);
//
//std::string str;
//nc::json::Get(document, "string", str);
//std::cout << str << std::endl;
//
//bool b;
//nc::json::Get(document, "bool", b);
//std::cout << b << std::endl;
//
//int i1;
//nc::json::Get(document, "integer1", i1);
//std::cout << i1 << std::endl;
//
//int i2;
//nc::json::Get(document, "integer2", i2);
//std::cout << i2 << std::endl;
//
//float f;
//nc::json::Get(document, "float", f);
//std::cout << f << std::endl;
//
//nc::Vector2 v2;
//nc::json::Get(document, "vector2", v2);
//std::cout << v2 << std::endl;
//
//nc::Color color;
//nc::json::Get(document, "color", color);
//std::cout << color << std::endl;
