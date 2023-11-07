#pragma once
#include "pch.h"
#include "TextureRegion.h"
#include "Component.h"

namespace Spite {
	class Sprite : public Component {
	public:
		Sprite(Entity&);
		void Update(double dt) override;
		void Draw(double dt) override;
		glm::vec4 colour;
		std::optional<TextureRegion> textureRegion;
	};

}