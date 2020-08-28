#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Core/Json.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "TileMap.h"

nc::Engine engine;
nc::Scene scene;

int main(int, char**)
{
	engine.Startup();

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);

	rapidjson::Document document;
	nc::json::Load("scene.txt", document);
	scene.Create(&engine);
	scene.Read(document);

	nc::TileMap tileMap;
	nc::json::Load("tileMap.txt", document);
	tileMap.Read(document);
	tileMap.Create(&scene);


	//std::vector<std::vector<int>> tiles = { { 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1 },
	//										{ 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1 } };
	//float xo = 32.0f;
	//float yo = 32.0f;
	//float sx = 64.0f;
	//float sy = 64.0f;

	//for (size_t y = 0; y < tiles.size(); y++)
	//{
	//	for (size_t x = 0; x < tiles[y].size(); x++)
	//	{
	//		if (tiles[y][x] == 1)
	//		{
	//			nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoTile");
	//			gameObject->m_transform.position = nc::Vector2{ xo, yo } + nc::Vector2{ (x * sx), (y * sy) };
	//			scene.AddGameObject(gameObject);
	//		}
	//	}
	//}

	//for (size_t i = 0; i < 10; i++)
	//{
	//	nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoTile");
	//	gameObject->m_transform.position = { nc::random(0, 800), nc::random(300, 450) };
	//	//gameObject->m_transform.angle = nc::random(0, 360);

	//	scene.AddGameObject(gameObject);
	//}

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
		scene.Update();

		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

		// draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();

		scene.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	engine.Shutdown();

	return 0;
}
