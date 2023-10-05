#pragma once
#include <glm/vec2.hpp>

namespace Spite {

	class Sprite {
		public:
		Sprite(glm::vec2 position, float z);
		Sprite();
		glm::vec2 position;
		glm::vec2 scale;
		float rotation;
		float z;
	};

}