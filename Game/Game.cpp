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
#include "EntityFactory.h"

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
waveEntity{ nullptr } {
	Spite::core->Register<PlayerComponent>("PlayerComponent");
	Spite::core->Register<BulletComponent>("BulletComponent");
	Spite::core->Register<LivingComponent>("LivingComponent");
	Spite::core->Register<EyeballComponent>("EyeballComponent");

	Spite::render->Camera().dimensions = {32, 18};
	Spite::render->BlackBars() = true;
	Spite::render->BackgroundColour() = {0.0,0.0,0.04};
	Spite::sound->SetGlobalVolume(0.25f);
	music = Spite::sound->LoadStreamAndPlay("song.ogg", 1.0f).Loop();
	
	Setup();
}

void Game::Setup() {
	srand(999);
	currentWave = 0;
	auto* root{ scene.GetRoot() };
	for(auto c : root->GetChildren()) {
		root->RemoveChild(scene.GetEntity(c));
	}
	music.Seek(0.0f);
	music.Play();
	waveEntity = scene.GetRoot()->AddChild(scene.CreateEntity());
	for (int i = 0; i < 16; i++) {
		root->AddChild(EntityFactory::Star(&scene, 1.0f, 0.5f, 0.2f));
	}
	for (int i = 0; i < 32; i++) {
		root->AddChild(EntityFactory::Star(&scene, 0.5f, 0.25f, 0.1f));
	}
	for (int i = 0; i < 64; i++) {
		root->AddChild(EntityFactory::Star(&scene, 0.25f, 0.125f, 0.0f));
	}
	playerEntityId = root->AddChild(EntityFactory::Player(&scene))->GetID();
	root->AddChild(EntityFactory::UIHealth(&scene));
	SpawnWave(waveEntity, currentWave);
}


void Game::Update(float dt)
{
	if(scene.GetEntitiesByTag("endscreen").size() > 0) {
		if (Spite::event->JustPressed(Spite::KeyValue::KV_R)) {
			Setup();
		}
	}else{
		//In game
		if (waveEntity->GetChildCount() == 0) {
			currentWave++;
			if (currentWave < 9) {
				SpawnWave(waveEntity, currentWave);
			} else {
				//Won
				scene.GetRoot()->AddChild(EntityFactory::UIEndScreen(&scene, true));
				music.Pause();
				Spite::sound->LoadSampleAndPlay("player_win.wav");
			}
		}
		if (!scene.GetEntity(playerEntityId)) {
			//Lost
			scene.GetRoot()->AddChild(EntityFactory::UIEndScreen(&scene, false));
			music.Pause();
			Spite::sound->LoadSampleAndPlay("player_lose.wav");
		}
		scene.Update(dt);
	}
	
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
		auto eyeball0{ EntityFactory::Eyeball(&scene, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactory::Eyeball(&scene, 11.0f, 0.5f) };
		eyeball0->transform.position = { 18.0f, -3 };
		eyeball1->transform.position = { 18.0f, 3 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		break;
	}
	case 1: {
		auto eyeball0{ EntityFactory::Eyeball(&scene, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactory::Eyeball(&scene, 9.0f, 0.0f) };
		auto eyeball2{ EntityFactory::Eyeball(&scene, 11.0f, 0.0f) };
		eyeball0->transform.position = { 18.0f, -5 };
		eyeball1->transform.position = { 18.0f, 0 };
		eyeball2->transform.position = { 18.0f, 5 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		parent->AddChild(std::move(eyeball2));
		break;
	}
	case 2: {
		auto eyeball0{ EntityFactory::Eyeball(&scene, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactory::Eyeball(&scene, 9.0f, 0.0f) };
		auto eyeball2{ EntityFactory::Eyeball(&scene, 7.0f, 0.0f) };
		auto eyeball3{ EntityFactory::Eyeball(&scene, 9.0f, 0.0f) };
		auto eyeball4{ EntityFactory::Eyeball(&scene, 11.0f, 0.0f) };
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
	case 3: {
		auto eyeball0{ EntityFactory::Eyeball(&scene, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactory::EyeballSpray(&scene, 9.0f, 0.0f) };
		auto eyeball2{ EntityFactory::Eyeball(&scene, 11.0f, 0.0f) };
		eyeball0->transform.position = { 18.0f, -5 };
		eyeball1->transform.position = { 18.0f, 0 };
		eyeball2->transform.position = { 18.0f, 5 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		parent->AddChild(std::move(eyeball2));
		break;
	}
	case 4: {
		auto eyeball0{ EntityFactory::EyeballSpray(&scene, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactory::EyeballSpray(&scene, 11.0f, 0.5f) };
		eyeball0->transform.position = { 18.0f, -3 };
		eyeball1->transform.position = { 18.0f, 3 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		break;
	}
	case 5: {
		auto eyeball0{ EntityFactory::EyeballWheel(&scene, 9.0f) };
		eyeball0->transform.position = { 18.0f, 0 };
		parent->AddChild(std::move(eyeball0));
		break;
	}
	case 6: {
		auto eyeball0{ EntityFactory::EyeballWheel(&scene, 9.0f, 0.1f, 12, 2.1f, 3.0f) };
		eyeball0->transform.position = { 18.0f, 0 };
		parent->AddChild(std::move(eyeball0));
		break;
	}
	case 7:
	{
		auto eyeball0{ EntityFactory::EyeballWheel(&scene, 9.0f, 0.1f, 12, 2.1f, 3.0f, false) };
		auto eyeball1{ EntityFactory::EyeballWheel(&scene, 9.0f, 0.1f, 12, 2.1f, 3.0f, true) };
		eyeball0->transform.position = { 18.0f, -4 };
		eyeball1->transform.position = { 18.0f, 4 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		break;
	}
	case 8:
	{
		auto eyeball0{ EntityFactory::EyeballWheel(&scene, 9.0f, 0.1f, 6, 1.1f, 3.0f, false) };
		auto eyeball1{ EntityFactory::EyeballWheel(&scene, 9.0f, 0.1f, 12, 2.1f, 3.0f, true) };
		auto eyeball2{ EntityFactory::EyeballWheel(&scene, 9.0f, 0.1f, 18, 3.1f, 3.0f, false) };
		eyeball0->transform.position = { 28.0f, 0 };
		eyeball1->transform.position = { 28.0f, 0 };
		eyeball2->transform.position = { 28.0f, 0 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		parent->AddChild(std::move(eyeball2));
		break;
	}
	}
}
