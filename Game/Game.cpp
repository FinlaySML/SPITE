#include "Game.h"
#include "PlayerComponent.h"
#include "FunctionComponent.h"
#include "BulletComponent.h"
#include "AnimatorComponent.h"
#include "LivingComponent.h"
#include "EyeballComponent.h"
#include "EntityFactory.h"
#include "WaveComponent.h"
#include "SceneFactory.h"

Spite::Application* Spite::CreateApp(int argc, char** argv)
{
	return new Game();
}

Game::Game() {
	Spite::core->Register<PlayerComponent>("PlayerComponent");
	Spite::core->Register<BulletComponent>("BulletComponent");
	Spite::core->Register<LivingComponent>("LivingComponent");
	Spite::core->Register<EyeballComponent>("EyeballComponent");
	Spite::core->Register<WaveComponent>("WaveComponent");
	Spite::core->Register<ManagerComponent>("ManagerComponent");
	scene.Load(SceneFactory::MainGame);
}

void Game::Update(float dt)
{
	scene.Update(dt);
}

void Game::Render(float dt)
{
	scene.Draw();
}

int Game::GetTickRate() {
	return 120;
}

void Game::OnQuit() {

}
