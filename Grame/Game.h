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
	Spite::Sprite playerSprite;
	std::unique_ptr<Spite::SpriteBatch> worldBatch;
	std::unique_ptr<Spite::SpriteBatch> spriteBatch;
	std::unique_ptr<Spite::Texture> testTexture;
	std::unique_ptr<Spite::Texture> testTexture2;
	std::unique_ptr<Spite::Texture> testTexture3;
};
