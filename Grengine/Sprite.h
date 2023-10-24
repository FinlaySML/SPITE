#pragma once
#include "pch.h"
#include "TextureRegion.h"

namespace Spite {

	class Sprite {
	public:
		Sprite(glm::vec2 position, float z);
		Sprite();
		glm::vec2 position;
		glm::vec2 scale;
		float rotation;
		float z;
		glm::vec4 colour;
		std::optional<TextureRegion> textureRegion;
	};

}