#pragma once
#include <chrono>
namespace Spite {
	using Clock = std::chrono::steady_clock;
	/// <summary>
	/// Quick and dirty Time system.
	/// Manages time between "ticks" (main loops)
	/// and "updates" (update loops)
	/// 
	/// </summary>
	
	//TODO: Bug where the update loop is SLOWER than intended when the application isn't doing anything
	class TimeSystem
	{
	public:
		TimeSystem(const int targetFramesPerSecond);
		/// <summary>
		/// Sleeps till the next frame 
		/// </summary>
		/// <returns>The frame delta in seconds</returns>
		const double GetFrameDelta();

		/// <summary>
		/// Get the tick delta
		/// </summary>
		/// <returns>The tick delta in seconds</returns>
		const double GetTickDelta();

		/// <summary>
		/// Get the number of ticks to execute
		/// </summary>
		/// <returns> 
		/// The number of ticks
		/// </returns>
		int GetTickCount();
	private:
		std::chrono::time_point<Clock>	LastFrameTime;
		std::chrono::time_point<Clock>	LastTickTime;
		const std::chrono::duration<double>	TargetFrameTime;
		const std::chrono::duration<double>	TargetTickTime;

		const int MaxTickCount;
		const double MaxFrameDelta;
	};
}
