#include "pch.h"
#include "TimeSystem.h"

using namespace std::chrono;
using dsec = duration<double>;

namespace Spite {
	TimeSystem::TimeSystem(const int targetFramesPerSecond) : targetTickTime{ 1.0 / targetFramesPerSecond }, maxTickCount{ 8 }, maxFrameDelta{ 1.0 / 15.0 }
	{		
		lastFrameTime = lastTickTime = Clock::now();
	}
	
	const double TimeSystem::GetFrameDelta()
	{
		dsec frameDelta = Clock::now() - lastFrameTime;
		frameDelta = Clock::now() - lastFrameTime;
		lastFrameTime = Clock::now();
		return std::min(maxFrameDelta, frameDelta.count());
	}
	const double TimeSystem::GetTickDelta()
	{
		return targetTickTime.count();
	}
	int TimeSystem::GetTickCount()
	{
		int tickCount = 0;
		auto now = Clock::now();
		while (now > lastTickTime) {
			lastTickTime += duration_cast<nanoseconds>(targetTickTime);
			tickCount++;
			if (tickCount == maxTickCount) {
				lastTickTime = now;
				break;
			}
		}
		return tickCount;
	}
}