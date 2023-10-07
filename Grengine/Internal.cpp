#include "pch.h"
#include "Internal.h"

#include "RenderSystem.h"
#include "EventSystem.h"
#include "SoundSystem.h"

int Spite::Internal::ExecuteGame(int argc, char** argv) {
	render->Initialise();
	event->Initialise();
	sound->Initialise();

	Spite::TimeSystem grTimeSystem{ 60 };
	std::unique_ptr<Spite::Application> app{ Spite::CreateApp(argc, argv) };

	//Maybe the application layer should be in charge of calling this?
	render->OpenWindow(1280, 720);
	render->CreateRenderer();

	float frameDelta = 1 / 60.0f;
	//Frame Loop
	while (true) {
		//Events
		if (event->ProcessEvents() == -1) {
			break;
		}
		//Tick
		int tickCount = grTimeSystem.GetTickCount();
		for (int i = 0; i < tickCount; i++) {
			app->Update(grTimeSystem.GetTickDelta());
		}
		//Frame
		app->Render(frameDelta);
		//Get next frames delta
		frameDelta = grTimeSystem.GetFrameDelta();
	}
	sound->Shutdown();
	event->Shutdown();
	render->Shutdown();
	return 0;
}