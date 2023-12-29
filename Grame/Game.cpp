#include "Game.h"
#include "RenderSystem.h"
#include "SoundSystem.h"
#include "EventSystem.h"
#include "CoreSystem.h"
#include "PlayerComponent.h"
#include "FunctionComponent.h"
#include "BulletComponent.h"
#include "AnimatorComponent.h"
#include "LivingComponent.h"
#include "EyeballComponent.h"
#include "EntityFactories.h"

Spite::Application* Spite::CreateApp(int argc, char** argv)
{
	return new Game();
}

//Layers
//[0,1) Background
//[1,2) Bullet
//[2,3) Enemy
//[3,4) Player

Game::Game() :
currentWave{ 0 },
waveParent{ scene.GetRoot()->AddChild(scene.CreateEntity())} {
	Spite::core->Register<PlayerComponent>("PlayerComponent");
	Spite::core->Register<BulletComponent>("BulletComponent");
	Spite::core->Register<LivingComponent>("LivingComponent");
	Spite::core->Register<EyeballComponent>("EyeballComponent");

	Spite::render->Camera().dimensions = {32, 18};
	Spite::render->BlackBars() = true;
	Spite::render->BackgroundColour() = {0.0,0.0,0.04};
	
	Spite::sound->LoadStreamAndPlay("song.ogg", 1.0f).Loop();
	
	auto* root{ scene.GetRoot() };
	for (int i = 0; i < 16; i++) {
		root->AddChild(EntityFactories::StarFactory(&scene, 1.0f, 0.5f, 0.2f));
	}
	for (int i = 0; i < 32; i++) {
		root->AddChild(EntityFactories::StarFactory(&scene, 0.5f, 0.25f, 0.1f));
	}
	for (int i = 0; i < 64; i++) {
		root->AddChild(EntityFactories::StarFactory(&scene, 0.25f, 0.125f, 0.0f));
	}
	root->AddChild(EntityFactories::PlayerFactory(&scene));
	SpawnWave(waveParent, 0);
	scene.Save("test_scene.txt");
}

void Game::Update(float dt)
{
	if(waveParent->GetChildCount() == 0) {
		currentWave++;
		if(currentWave < 4) {
			SpawnWave(waveParent, currentWave);
		}
	}
	
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

void Game::SpawnWave(Spite::Entity* parent, int waveNumber) {
	switch(waveNumber) {
	case 0: {
		auto eyeball0{ EntityFactories::EyeballFactory(&scene, 2.0f, 0.7f, 11.0f, 0.0f) };
		eyeball0->transform.position = { 18.0f, 0 };
		parent->AddChild(std::move(eyeball0));
		break;
	}
	case 1: {
		auto eyeball0{ EntityFactories::EyeballFactory(&scene, 2.0f, 0.7f, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactories::EyeballFactory(&scene, 2.0f, 0.7f, 11.0f, 0.5f) };
		eyeball0->transform.position = { 18.0f, -3 };
		eyeball1->transform.position = { 18.0f, 3 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		break;
	}
	case 2: {
		auto eyeball0{ EntityFactories::EyeballFactory(&scene, 2.0f, 0.7f, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactories::EyeballFactory(&scene, 2.0f, 0.7f, 9.0f, 0.0f) };
		auto eyeball2{ EntityFactories::EyeballFactory(&scene, 2.0f, 0.7f, 11.0f, 0.0f) };
		eyeball0->transform.position = { 18.0f, -5 };
		eyeball1->transform.position = { 18.0f, 0 };
		eyeball2->transform.position = { 18.0f, 5 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		parent->AddChild(std::move(eyeball2));
		break;
	}
	case 3:
	{
		auto eyeball0{ EntityFactories::EyeballFactory(&scene, 2.0f, 0.7f, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactories::EyeballFactory(&scene, 2.0f, 0.7f, 9.0f, 0.0f) };
		auto eyeball2{ EntityFactories::EyeballFactory(&scene, 2.0f, 0.7f, 7.0f, 0.0f) };
		auto eyeball3{ EntityFactories::EyeballFactory(&scene, 2.0f, 0.7f, 9.0f, 0.0f) };
		auto eyeball4{ EntityFactories::EyeballFactory(&scene, 2.0f, 0.7f, 11.0f, 0.0f) };
		eyeball0->transform.position = { 18.0f, -5.0f };
		eyeball1->transform.position = { 18.0f, -2.5f };
		eyeball2->transform.position = { 18.0f, 0.0f };
		eyeball3->transform.position = { 18.0f, 2.5f };
		eyeball4->transform.position = { 18.0f, 5.0f };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		parent->AddChild(std::move(eyeball2));
		parent->AddChild(std::move(eyeball3));
		parent->AddChild(std::move(eyeball4));
		break;
	}
	}
}
