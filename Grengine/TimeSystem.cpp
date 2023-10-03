#include "pch.h"
#include "TimeSystem.h"

using namespace std::chrono;
using dsec = duration<double>;

namespace Spite {
	TimeSystem::TimeSystem(const int targetFramesPerSecond) : TargetTickTime{ 1.0 / 60.0 }, TargetFrameTime{ 1.0 / 60.0 }, MaxTickCount{ 8 }, MaxFrameDelta{ 1.0 / 15.0 }
	{		
		LastFrameTime = LastTickTime = Clock::now();
	}
	
	const double TimeSystem::GetFrameDelta()
	{
		dsec frameDelta = Clock::now() - LastFrameTime;
		if (frameDelta < TargetFrameTime) {
			std::this_thread::sleep_for(TargetFrameTime - frameDelta);
		}
		frameDelta = Clock::now() - LastFrameTime;
		LastFrameTime = Clock::now();
		return std::min(MaxFrameDelta, frameDelta.count());
	}
	const double TimeSystem::GetTickDelta()
	{
		return TargetTickTime.count();
	}
	int TimeSystem::GetTickCount()
	{
		int tickCount = 0;
		auto now = Clock::now();
		while (now > LastTickTime) {
			LastTickTime += duration_cast<nanoseconds>(TargetTickTime);
			tickCount++;
			if (tickCount == MaxTickCount) {
				LastTickTime = now;
				break;
			}
		}
		return tickCount;
	}
}