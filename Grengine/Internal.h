#pragma once

#include "Application.h"
#include "TimeSystem.h"
#include "pch.h"

namespace Spite {
	/// <summary>
	/// Interals of SPITE, you shouldn't call any of these functions ever
	/// </summary>
	class Internal {
	public:
		static int ExecuteGame(int argc, char** argv);
	};
}
