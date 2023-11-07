#include "Game.h"
#include "RenderSystem.h"
#include "SoundSystem.h"
#include "EventSystem.h"

Spite::Application* Spite::CreateApp(int argc, char** argv)
{
	return new Game();
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
	//Test
	testEntity.AddComponent<Spite::Sprite>().textureRegion.emplace(testTexture.get());
	//Player
	playerEntity.AddComponent<Spite::Sprite>().colour = {1,0,0,1};
}

void Game::Update(double dt)
{
	spriteBatch->Clear();
	glm::vec2 moveDir{0, 0};
	if(Spite::event->IsPressed(Spite::KeyValue::KV_D)) {
		moveDir.x++;
	}
	if(Spite::event->IsPressed(Spite::KeyValue::KV_A)) {
		moveDir.x--;
	}
	if (Spite::event->IsPressed(Spite::KeyValue::KV_W)) {
		moveDir.y++;
	}
	if (Spite::event->IsPressed(Spite::KeyValue::KV_S)) {
		moveDir.y--;
	}
	if(glm::length(moveDir) > 0) {
		moveDir = glm::normalize(moveDir);
		playerEntity.rotation = std::atan2(moveDir.x, moveDir.y);
	}
	moveDir *= 3.0f;
	playerEntity.position += moveDir * dt;
	spriteBatch->Add(testEntity.GetComponent<Spite::Sprite>());
	spriteBatch->Add(playerEntity.GetComponent<Spite::Sprite>());
	Spite::render->Camera().position = playerEntity.position;
	//Toggle fullscreen
	if(Spite::event->GetDownCount(Spite::KeyValue::KV_F11) % 2 == 1){
		Spite::render->SetFullscreen(!Spite::render->GetFullscreen());
	}
}

void Game::Render(double dt)
{
	Spite::render->Clear();
	spriteBatch->Draw();
	Spite::render->Display();
}
