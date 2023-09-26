#include "Core.h"

#include "RenderSystem.h"
#include "EventSystem.h"

namespace Spite {

	Core::Core(int argc, char** argv) :
		grApp{Spite::CreateApp(argc, argv)}, //Create the application layer
		grTimeSystem{ 60 }						//Targeting 60 frames per second
	{
		//Initialise Subsystems
		grRenderSystem->Initialise();
		grEventSystem->Initialise();
	}

	void Core::OpenWindow(int ScreenWidth, int ScreenHeight) {
		grRenderSystem->OpenWindow(ScreenWidth, ScreenHeight);
		grRenderSystem->CreateRenderer();
	}

	//Our main loop
	int Core::Run() {

		//Maybe the application layer should be in charge of calling this?
		OpenWindow(1280, 720);

		float frameDelta = 1/60.0f;
		//Frame Loop
		while (true) {
			//Events
			if (ProcessEvents() == -1) {
				break;
			}
			//Tick
			int tickCount = grTimeSystem.GetTickCount();
			for (int i = 0; i < tickCount; i++) {
				Update(grTimeSystem.GetTickDelta());
			}
			//Frame
			Render(frameDelta);
			//Get next frames delta
			frameDelta = grTimeSystem.GetFrameDelta();
		}
		Close();
		return 0;
	}
	int Core::ProcessEvents()
	{
		return grEventSystem->ProcessEvents();
	}
	void Core::Update(double dt)
	{
		grApp->Update(dt);
	}
	void Core::Render(double dt)
	{		
		grApp->Render(dt);
	}
	void Core::Close()
	{
		grEventSystem->Shutdown();
		grRenderSystem->Shutdown();
	}
}