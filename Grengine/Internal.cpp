#include "pch.h"
#include "Internal.h"

#include "RenderSystem.h"
#include "EventSystem.h"
#include "SoundSystem.h"

int Spite::Internal::ExecuteGame(int argc, char** argv) {
	render->Initialise();
	event->Initialise();
	sound->Initialise();

	render->OpenWindow(1280, 720);
	render->CreateRenderer();

	Spite::TimeSystem grTimeSystem{ 60 };
	std::unique_ptr<Spite::Application> app{ Spite::CreateApp(argc, argv) };

	double frameDelta = 1.0 / 60.0;
	//Frame Loop
	while (true) {
		//Events
		if (event->ProcessEvents() == -1) {
			break;
		}
		//Tick
		int tickCount = grTimeSystem.GetTickCount();
		for (int i = 0; i < tickCount; i++) {
			event->UpdateStart();
			app->Update(grTimeSystem.GetTickDelta());
			event->UpdateEnd();
		}
		//Frame
		event->RenderStart();
		app->Render(frameDelta);
		event->RenderEnd();
		//Get next frames delta
		frameDelta = grTimeSystem.GetFrameDelta();
	}
	sound->Shutdown();
	event->Shutdown();
	render->Shutdown();
	return 0;
}