#pragma once
#include "pch.h"
#include "TextureRegion.h"
#include "Component.h"

namespace Spite {
	class SpriteComponent : public Component {
	public:
		SpriteComponent(Entity* parent, ComponentID id);
		void Draw(const glm::mat3x3& worldTransform) override;
		void Serialise(YAML::Emitter&) const override;
		void Deserialise(const YAML::Node&) override;
		glm::vec4 colour;
		std::optional<TextureRegion> textureRegion;
	};
}