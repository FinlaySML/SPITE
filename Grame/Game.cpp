#include "Game.h"
#include "RenderSystem.h"
#include "SoundSystem.h"
#include "EventSystem.h"

Spite::Application* Spite::CreateApp(int argc, char** argv)
{
	return new Game();
}

Game::Game() : 
	worldBatch{ Spite::render->CreateSpriteBatch() },
	spriteBatch{ Spite::render->CreateSpriteBatch() },
	testTexture{ Spite::render->CreateTexture() },
	testTexture2{ Spite::render->CreateTexture() },
	testTexture3{ Spite::render->CreateTexture() }
{
	testTexture->LoadFromFile("test.png");
	testTexture2->LoadFromFile("test2.png");
	testTexture3->LoadFromFile("test4.png");
	coinSample = Spite::sound->LoadSample("coin1.wav");

	Spite::render->Camera().unitHeight = 15.0f;
	Spite::render->BackgroundColour() = {0.7,0.5,1.0};
	Spite::sound->Play(coinSample, 1.0f);
	//Sprites
	Spite::Sprite sprite{};
	sprite.textureRegion.emplace(testTexture.get());
	for (int i = 0; i < 1'000; i++) {
		float f = sqrtf(i * 12.0f);
		sprite.position = { sin(f) * f * 0.2f, cos(f) * f * 0.2f };
		sprite.rotation = f;
		worldBatch->Add(sprite);
	}
	sprite.textureRegion.emplace(testTexture2.get());
	worldBatch->Add(sprite);
	sprite.textureRegion.emplace(testTexture3.get());
	worldBatch->Add(sprite);
	playerSprite.colour = {1,0,0,1};
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
		playerSprite.rotation = std::atan2(moveDir.x, moveDir.y);
	}
	moveDir *= 3.0f;
	playerSprite.position += moveDir * dt;
	spriteBatch->Add(playerSprite);
	Spite::render->Camera().position = playerSprite.position;
	//Toggle fullscreen
	if(Spite::event->GetDownCount(Spite::KeyValue::KV_F11) % 2 == 1){
		Spite::render->SetFullscreen(!Spite::render->GetFullscreen());
	}
}

void Game::Render(double dt)
{
	Spite::render->Clear();
	worldBatch->Draw();
	spriteBatch->Draw();
	Spite::render->Display();
}
