#include "Game.h"
#include "RenderSystem.h"
#include "SoundSystem.h"

Spite::Application* Spite::CreateApp(int argc, char** argv)
{
	return new Game();
}

Game::Game()
{
	auto coinSample = Spite::sound->LoadSample("coin1.wav");
	Spite::sound->Play(coinSample);
}

void Game::Update(double dt)
{
	//std::cout << "Update " << dt << "\n";
}

void Game::Render(double dt)
{
	Spite::render->Clear();
	Spite::render->Camera().position = { 0, 0 };
	Spite::render->Camera().unitHeight = 1000.0f;
	Spite::Sprite sprite{};
	for(int i = 0; i < 250'000; i++){
		float f = sqrtf(i);
		sprite.position = {cos(f)*f, sin(f)*f};
		Spite::render->DrawSprite(sprite);
	}
	Spite::render->Display();
}
