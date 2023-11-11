#include "pch.h"
#include "CoreSystem.h"
#include "Sprite.h"

Spite::CoreSystem* Spite::core = new Spite::CoreSystem();

int Spite::CoreSystem::Initialise() {
	Register<Spite::Sprite>();
	return 0;
}

int Spite::CoreSystem::Shutdown() {
	return 0;
}
