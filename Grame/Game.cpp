#include "Game.h"
#include "RenderSystem.h"
#include <iostream>

//Create the application layer
//See Application.h
Spite::Application* Spite::CreateApp(int argc, char** argv)
{
	return new Game();
}

Game::Game()
{
}

void Game::Update(double dt)
{
	std::cout << "Update " << dt << "\n";
}

void Game::Render(double dt)
{
	static double a{ 0.0 };
	a += dt;
	static double b{ 0.0 };
	b += 1.0;
	std::cout << a / b << "\n";
}
