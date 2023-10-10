#include "Game.h"
#include "RenderSystem.h"
#include "SoundSystem.h"
#include "EventSystem.h"

Spite::Application* Spite::CreateApp(int argc, char** argv)
{
	return new Game();
}

Game::Game()
{
	coinSample = Spite::sound->LoadSample("coin1.wav");
	Spite::render->Camera().unitHeight = 30.0f;
	Spite::render->BackgroundColour() = {0.6,0.6,1};
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
		float f = sqrtf(i*12);
		sprite.position = {sin(f)*f*0.2f, cos(f) * f * 0.2f };
		sprite.rotation = f;
		Spite::render->DrawSprite(sprite);
	}
	Spite::render->Display();
}
