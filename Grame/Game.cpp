#include "Game.h"
#include "RenderSystem.h"
#include "SoundSystem.h"
#include "EventSystem.h"
#include "CoreSystem.h"
#include "PlayerComponent.h"

Spite::Application* Spite::CreateApp(int argc, char** argv)
{
	return new Game();
}

std::unique_ptr<Spite::Entity> TestFactory(Spite::Scene* scene) {
	auto e = scene->CreateEntity();
	auto& pSprite = e->AddComponent<Spite::SpriteComponent>();
	pSprite.textureRegion.emplace(Spite::render->GetTexture("test.png"));
	e->transform.position.x = (rand() / (float)RAND_MAX) * 16.0f - 8.0f;
	e->transform.position.y = (rand() / (float)RAND_MAX) * 16.0f - 8.0f;
	e->transform.rotation = (rand() / (float)RAND_MAX) * glm::two_pi<float>();
	return e;
}

std::unique_ptr<Spite::Entity> PlayerFactory(Spite::Scene* scene) {
	auto e = scene->CreateEntity();
	auto& pSprite = e->AddComponent<Spite::SpriteComponent>();
	pSprite.textureRegion.emplace(Spite::render->GetTexture("ship.png"));
	e->AddComponent<PlayerComponent>();
	return e;
}

Game::Game()
{
	Spite::core->Register<PlayerComponent>("PlayerComponent");

	Spite::render->Camera().dimensions = {32, 18};
	Spite::render->BlackBars() = true;
	Spite::render->BackgroundColour() = {0.0,0.0,0.04};
	
	Spite::sound->LoadSampleAndPlay("coin1.wav", 1.0f).Speed(0.2f).Delay(0.0f);
	Spite::sound->LoadSampleAndPlay("coin1.wav", 1.0f).Speed(0.4f).Delay(1.0f);
	Spite::sound->LoadSampleAndPlay("coin1.wav", 1.0f).Speed(0.8f).Delay(2.0f);

	auto* root{scene.GetRoot()};
	for (int i = 0; i < 4; i++) {
		root->AddChild(TestFactory(&scene));
	}
	root->AddChild(PlayerFactory(&scene));
	scene.Save("test_scene.txt");
}

void Game::Update(float dt)
{
	scene.Update(dt);
	//Toggle fullscreen
	if(Spite::event->JustPressed(Spite::KeyValue::KV_F11)){
		Spite::render->SetFullscreen(!Spite::render->GetFullscreen());
	}
}

void Game::Render(float dt)
{
	Spite::render->Clear();
	scene.Draw();
	Spite::render->Display();
}

int Game::GetTickRate() {
	return 120;
}

void Game::OnQuit() {

}
