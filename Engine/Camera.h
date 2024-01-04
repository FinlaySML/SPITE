#pragma once
#include "pch.h"

namespace Spite {
	class Camera {
	public:
		Camera(glm::vec2 position, glm::vec2 dimensions = {16, 9}, float rotation = 0.0f);
		glm::vec2 position;
		glm::vec2 dimensions;
		float rotation;
	};
}
