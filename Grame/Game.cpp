#include "Game.h"
#include "RenderSystem.h"

//Create the application layer
//See Application.h
Spite::Application* Spite::CreateApp(int argc, char** argv)
{
	return new Game();
}

Game::Game()
{
}

void Game::Update(double dt)
{
	//std::cout << "Update " << dt << "\n";
}

void Game::Render(double dt)
{
	Spite::grRenderSystem->Clear();
	Spite::grRenderSystem->Camera().position = { 0, 0 };
	Spite::grRenderSystem->Camera().unitHeight = 1000.0f;
	Spite::Sprite sprite{};
	for(int i = 0; i < 250'000; i++){
		float f = sqrtf(i);
		sprite.position = {cos(f)*f, sin(f)*f};
		Spite::grRenderSystem->DrawSprite(sprite);
	}
	Spite::grRenderSystem->Display();
}
