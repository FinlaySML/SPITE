#pragma once
#include "pch.h"
#include "TextureRegion.h"
#include "Component.h"

namespace Spite {
	class AnimatorComponent : public Component {
	public:
		AnimatorComponent(Entity* parent, ComponentID id);
		void Update(float dt) final;
		void Serialise(YAML::Emitter&) const override;
		void Deserialise(const YAML::Node&) override;
		ComponentID target;
		std::optional<TextureRegion> spriteSheet;
		glm::ivec2 slices;
		float frame;
		float fps;
	};
}