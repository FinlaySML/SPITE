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
	Spite::sound->Play(coinSample, 1.0f);
}

void Game::Update(double dt)
{
}

void Game::Render(double dt)
{
	Spite::render->Clear();
	Spite::Sprite sprite{};
	for(int i = 0; i < 50'000; i++){
		float f = sqrtf(i);
		sprite.position = {cos(f)*f, sin(f)*f};
		Spite::render->DrawSprite(sprite);
	}
	Spite::render->Display();
}
