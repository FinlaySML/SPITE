#include "Game.h"
#include "RenderSystem.h"
#include "SoundSystem.h"
#include "EventSystem.h"
#include "PlayerComponent.h"

Spite::Application* Spite::CreateApp(int argc, char** argv)
{
	return new Game();
}

void TestFactory(Spite::Entity& e, Spite::Texture* tex) {
	auto& pSprite = e.AddComponent<Spite::Sprite>();
	pSprite.textureRegion.emplace(tex);
}

void PlayerFactory(Spite::Entity& e, Spite::Texture* tex) {
	auto& pSprite = e.AddComponent<Spite::Sprite>();
	pSprite.colour = { 1,0,0,1 };
	pSprite.textureRegion.emplace(tex);
	e.scale.y = 0.7;
	e.AddComponent<PlayerComponent>();
}

Game::Game() : 
	spriteBatch{ Spite::render->CreateSpriteBatch() },
	testTexture{ Spite::render->CreateTexture() }
{
	testTexture->LoadFromFile("test.png");
	coinSample = Spite::sound->LoadSample("coin1.wav");

	Spite::render->Camera().unitHeight = 15.0f;
	Spite::render->BackgroundColour() = {0.7,0.5,1.0};
	Spite::sound->Play(coinSample, 1.0f);

	TestFactory(testEntity, testTexture.get());
	PlayerFactory(playerEntity, testTexture.get());
}

void Game::Update(double dt)
{
	testEntity.Update(dt);
	playerEntity.Update(dt);
	//Toggle fullscreen
	if(Spite::event->GetDownCount(Spite::KeyValue::KV_F11) % 2 == 1){
		Spite::render->SetFullscreen(!Spite::render->GetFullscreen());
	}
}

void Game::Render(double dt)
{
	Spite::render->Clear();
	spriteBatch->Clear();
	spriteBatch->Add(testEntity.GetComponent<Spite::Sprite>());
	spriteBatch->Add(playerEntity.GetComponent<Spite::Sprite>());
	spriteBatch->Draw();
	Spite::render->Display();
}
