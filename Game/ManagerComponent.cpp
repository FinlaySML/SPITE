#include "ManagerComponent.h"
#include "SoundSystem.h"
#include "Entity.h"
#include "Scene.h"
#include "EventSystem.h"
#include "SceneFactory.h"
#include "PlayerComponent.h"
#include "WaveComponent.h"
#include "EntityFactory.h"
#include "RenderSystem.h"

ManagerComponent::ManagerComponent(Spite::Entity* parent, Spite::ComponentID id) : Component(parent, id) {
	music = Spite::sound->LoadStreamAndPlay("song.ogg", 1.0f).Loop();
	paused = Spite::PauseState::NO;
}

void ManagerComponent::Update(float dt) {
	auto* entity{ GetEntity() };
	auto* scene{ entity->GetScene() };
	auto* root{ scene->GetRoot() };
	//Toggle fullscreen
	if (Spite::event->JustPressed(Spite::KeyValue::KV_F11)) {
		Spite::render->SetFullscreen(!Spite::render->GetFullscreen());
	}
	//End screen, press r to restart
	if (scene->GetEntitiesByTag("endscreen").size() > 0) {
		entity->paused = Spite::PauseState::YES;
		if (Spite::event->JustPressed(Spite::KeyValue::KV_R)) {
			scene->LoadDeferred(SceneFactory::MainGame);
		}
		return;
	}
	//In game
	if(auto wc{ (WaveComponent*)scene->GetComponent(waveComponentId) }) {
		if(wc->finished) {
			root->AddChild(EntityFactory::UIEndScreen(scene, true));
			music.Pause();
			Spite::sound->LoadSampleAndPlay("player_win.wav");
		}
	}
	if(!scene->GetComponent(playerComponentId)) {
		//Lost
		root->AddChild(EntityFactory::UIEndScreen(scene, false));
		music.Pause();
		Spite::sound->LoadSampleAndPlay("player_lose.wav");
	}
}
