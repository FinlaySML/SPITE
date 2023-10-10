#pragma once
#include <Spite.h>
#include "SoundSystem.h"
#include "SpriteBatch.h"

class Game : public Spite::Application
{
public:
	Game();
	void Update(double dt) final;
	void Render(double dt) final;
private:
	Spite::SoundSystem::SampleID coinSample;
	std::unique_ptr<Spite::SpriteBatch> testBatch;
};
