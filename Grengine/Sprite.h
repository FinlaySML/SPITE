#pragma once
#include "pch.h"
#include "TextureRegion.h"
#include "Component.h"

namespace Spite {
	class Sprite : public Component {
	public:
		Sprite(Entity&);
		void Draw(double dt) override;
		const std::string& GetName() override;
		void Serialise(YAML::Emitter&) override;
		glm::vec4 colour;
		std::optional<TextureRegion> textureRegion;
		static const std::string name;
	};

}