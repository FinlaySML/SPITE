#include "Game.h"
#include "RenderSystem.h"
#include "SoundSystem.h"
#include "EventSystem.h"
#include "PlayerComponent.h"

Spite::Application* Spite::CreateApp(int argc, char** argv)
{
	return new Game();
}

std::unique_ptr<Spite::Entity> TestFactory() {
	auto e = std::make_unique<Spite::Entity>();
	auto& pSprite = e->AddComponent<Spite::Sprite>();
	pSprite.textureRegion.emplace(Spite::render->GetTexture("test.png"));
	e->position.x = (rand() / (float)RAND_MAX) * 32.0f - 16.0f;
	e->position.y = (rand() / (float)RAND_MAX) * 32.0f - 16.0f;
	e->rotation = (rand() / (float)RAND_MAX) * glm::two_pi<float>();
	return e;
}

std::unique_ptr<Spite::Entity> PlayerFactory() {
	auto e = std::make_unique<Spite::Entity>();
	auto& pSprite = e->AddComponent<Spite::Sprite>();
	pSprite.colour = { 1,0,0,1 };
	pSprite.textureRegion.emplace(Spite::render->GetTexture("test.png"));
	e->scale.y = 0.7f;
	e->AddComponent<PlayerComponent>();
	return e;
}

Game::Game()
{
	coinSample = Spite::sound->LoadSample("coin1.wav");

	Spite::render->Camera().unitHeight = 15.0f;
	Spite::render->BackgroundColour() = {0.7,0.5,1.0};
	
	Spite::sound->Play(coinSample, 1.0f);
	for(int i = 0; i < 1000; i++) {
		root.AddChild(TestFactory());
	}
	root.AddChild(PlayerFactory());
}

void Game::Update(double dt)
{
	root.Update(dt);
	//Toggle fullscreen
	if(Spite::event->GetDownCount(Spite::KeyValue::KV_F11) % 2 == 1){
		Spite::render->SetFullscreen(!Spite::render->GetFullscreen());
	}
}

void Game::Render(double dt)
{
	Spite::render->Clear();
	root.Draw(dt);
	Spite::render->Display();
}
