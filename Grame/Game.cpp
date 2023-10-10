#include "Game.h"
#include "RenderSystem.h"
#include "SoundSystem.h"
#include "EventSystem.h"

Spite::Application* Spite::CreateApp(int argc, char** argv)
{
	return new Game();
}

Game::Game() : testBatch{Spite::render->CreateSpriteBatch()}
{
	coinSample = Spite::sound->LoadSample("coin1.wav");
	Spite::render->Camera().unitHeight = 1000.0f;
	Spite::render->BackgroundColour() = {0.6,0.6,1};
	Spite::sound->Play(coinSample, 1.0f);
	//Sprites
	Spite::Sprite sprite{};
	for (int i = 0; i < 1'000'000; i++) {
		float f = sqrtf(i * 12);
		sprite.position = { sin(f) * f * 0.2f, cos(f) * f * 0.2f };
		sprite.rotation = f;
		testBatch->Add(sprite);
	}
}

void Game::Update(double dt)
{
}

void Game::Render(double dt)
{
	std::cout << (int)std::floor(1.0f/dt) << std::endl;
	Spite::render->Clear();
	testBatch->Draw();
	Spite::render->Display();
}
