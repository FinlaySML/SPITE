#pragma once
namespace Spite {
	/// <summary>
	/// Interface to the application layer
	/// This should be supplied by the Game project
	/// </summary>
	class Application
	{
	public:
		/// <summary>
		/// Game logic, executed before Render
		/// </summary>
		/// <param name="dt"> (delta time) Time since the last Update</param>
		virtual void Update(double dt) = 0;
		/// <summary>
		/// Render logic
		/// </summary>
		virtual void Render(double dt) = 0;
		/// <summary>
		/// The game will Update this many times a second
		/// The game will also Render this many times a second (or at the refresh-rate, whichever is lower)
		/// A value of 30 or 60 would be typical
		/// </summary>
		/// <returns></returns>
		virtual int GetTickRate() = 0;
		/// <summary>
		/// Called when the user quits the application, will also be called when Spite::event->Quit(); is called
		/// </summary>
		virtual void OnQuit() = 0;
	};
	
	extern Application* CreateApp(int argc, char** argv);
}