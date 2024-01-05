#pragma once
#include <Spite.h>
#include "SoundSystem.h"
#include "SpriteBatch.h"
#include "Scene.h"
#include "SoundHandle.h"

class Game : public Spite::Application
{
public:
	Game();
	void Update(float dt) final;
	void Render(float dt) final;
	int GetTickRate() final;
	void OnQuit() final;
private:
	void Setup();
	Spite::Scene scene;
};
