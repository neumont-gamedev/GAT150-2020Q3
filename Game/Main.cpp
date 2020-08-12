#include "pch.h"
#include "Engine.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/PlayerController.h"
#include "Core/Json.h"

nc::Engine engine;

int main(int, char**)
{
	engine.Startup();

	nc::GameObject player;
	player.Create(&engine);
	player.m_transform.position = { 400, 300 };
	
	nc::Component* component;
	component = new nc::PhysicsComponent;
	player.AddComponent(component);
	component->Create();
	
	component = new nc::SpriteComponent;
	player.AddComponent(component);
	component->Create();

	component = new nc::PlayerController;
	player.AddComponent(component);
	component->Create();

	nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());
	nc::Texture* car = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", engine.GetSystem<nc::Renderer>());

	float angle{ 0 };
	nc::Vector2 position{ 400, 300 };
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

		quit = (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED);

		player.Update();




		// draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();

		background->Draw({ 0, 0 });

		// player sprite draw
		//car->Draw({ 64, 110, 60, 112 }, position, { 1, 1 }, angle);
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
