#pragma once
#include <glm/vec2.hpp>

namespace Spite {
	class Camera {
		public:
		Camera(glm::vec2 position, float unitHeight = 9.0f);
		glm::vec2 position;
		float unitHeight;
	};
}
