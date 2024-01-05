#include "SceneFactory.h"
#include "ManagerComponent.h"
#include "EntityFactory.h"
#include "WaveComponent.h"
#include "RenderSystem.h"
#include "SoundSystem.h"

void SceneFactory::MainGame(Spite::Scene& scene) {
	Spite::render->Camera().dimensions = { 32, 18 };
	Spite::render->BlackBars() = true;
	Spite::render->BackgroundColour() = { 0.0,0.0,0.04 };
	Spite::sound->SetGlobalVolume(0.25f);
    auto* root{ scene.GetRoot() };
    auto& cManager{root->AddComponent<ManagerComponent>()};
    root->AddChild(EntityFactory::Wave(&scene, cManager));
	for (int i = 0; i < 16; i++) {
		root->AddChild(EntityFactory::Star(&scene, 1.0f, 0.5f, 0.2f));
	}
	for (int i = 0; i < 32; i++) {
		root->AddChild(EntityFactory::Star(&scene, 0.5f, 0.25f, 0.1f));
	}
	for (int i = 0; i < 64; i++) {
		root->AddChild(EntityFactory::Star(&scene, 0.25f, 0.125f, 0.0f));
	}
	root->AddChild(EntityFactory::Player(&scene, cManager));
	root->AddChild(EntityFactory::UIHealth(&scene));
}
