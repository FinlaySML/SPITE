#pragma once

#include "Application.h"
#include "TimeSystem.h"
#include "pch.h"

namespace Spite {
	class Core
	{
	public:
		Core(int argc, char** argv);

		int		Run();

	private:
		void	OpenWindow(int ScreenWidth, int ScreenHeight);

		/// <summary>
		/// Get the event handler to process any events
		/// </summary>
		/// <returns>-1 on a Quit event</returns>
		int		ProcessEvents();
		void	Update(double dt);
		void	Render(double dt);

		void	Close();

	private:
		std::unique_ptr<Spite::Application> grApp;
		TimeSystem grTimeSystem;
	};
}
