#pragma once
#include <Spite.h>

class Game : public Spite::Application
{
public:
	Game();
	void Update(double dt) override final;
	void Render() override final;
};
