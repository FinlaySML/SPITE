#include "pch.h"
#include "Internal.h"

#include "RenderSystem.h"
#include "EventSystem.h"
#include "SoundSystem.h"
#include "CoreSystem.h"

#include "Entity.h"

using namespace std::chrono_literals;

int Spite::Internal::ExecuteGame(int argc, char** argv) {
	//Register components
	core->Initialise();
	render->Initialise();
	event->Initialise();
	sound->Initialise();

	render->OpenWindow(1280, 720);
	render->CreateRenderer();
	
	std::unique_ptr<Spite::Application> app{ Spite::CreateApp(argc, argv) };
	int tickRate{ app->GetTickRate() };
#ifdef _DEBUG
	if (tickRate <= 10) {
		std::cout << std::format("YourApplication->GetTickRate() returned {}, which is very low. This message will only appear in debug mode.", tickRate) << std::endl;
	}else if(tickRate >= 200) {
		std::cout << std::format("YourApplication->GetTickRate() returned {}, which is very high. This message will only appear in debug mode.", tickRate) << std::endl;
	}
#endif
	Spite::TimeSystem timeSystem{ tickRate };
	double frameDelta = 1.0 / 60.0;
	//Frame Loop
	while (true) {
		//Tick
		int tickCount = timeSystem.GetTickCount();
		while(tickCount == 0){
			std::this_thread::sleep_for(1ms);
			tickCount = timeSystem.GetTickCount();
		}
		for (int i = 0; i < tickCount; i++) {
			//Events
			event->ProcessEvents();
			//Update
			app->Update(timeSystem.GetTickDelta());
			event->UpdateEnd();
		}
		//Frame
		app->Render(frameDelta);
		//Get next frames delta
		frameDelta = timeSystem.GetFrameDelta();
		//Quit
		if(event->HasQuit()){
			app->OnQuit();
			break;
		}
	}
	sound->Shutdown();
	event->Shutdown();
	render->Shutdown();
	core->Shutdown();
	return 0;
}