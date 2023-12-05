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

std::unique_ptr<Spite::Entity> TestFactory() {
	auto e = std::make_unique<Spite::Entity>();
	auto& pSprite = e->AddComponent<Spite::Sprite>();
	pSprite.textureRegion.emplace(Spite::render->GetTexture("test.png"));
	e->position.x = (rand() / (float)RAND_MAX) * 16.0f - 8.0f;
	e->position.y = (rand() / (float)RAND_MAX) * 16.0f - 8.0f;
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
	Spite::core->Register<PlayerComponent>();

	Spite::render->Camera().dimensions *= 1.7f;
	Spite::render->BlackBars() = true;
	Spite::render->BackgroundColour() = {0.0,0.0,0.04};
	
	Spite::sound->LoadSampleAndPlay("coin1.wav", 1.0f).Speed(0.2f).Delay(0.0f);
	Spite::sound->LoadSampleAndPlay("coin1.wav", 1.0f).Speed(0.4f).Delay(1.0f);
	Spite::sound->LoadSampleAndPlay("coin1.wav", 1.0f).Speed(0.8f).Delay(2.0f);
	/*root = std::make_unique<Spite::Entity>();
	for (int i = 0; i < 4; i++) {
		root->AddChild(TestFactory());
	}
	root->AddChild(PlayerFactory());*/
	//Spite::core->SaveScene(*root, "test_scene.txt");
	root = Spite::core->LoadScene("test_scene.txt");
}

void Game::Update(double dt)
{
	root->Update(dt);
	//Toggle fullscreen
	if(Spite::event->JustPressed(Spite::KeyValue::KV_F11)){
		Spite::render->SetFullscreen(!Spite::render->GetFullscreen());
	}
}

void Game::Render(double dt)
{
	Spite::render->Clear();
	root->Draw(dt);
	Spite::render->Display();
}

int Game::GetTickRate() {
	return 30;
}

void Game::OnQuit() {

}
