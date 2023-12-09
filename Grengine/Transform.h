#pragma once
#include "pch.h"

namespace Spite {
	struct Transform {
		Transform();
		glm::vec2 position;
		glm::vec2 scale;
		float rotation;
		glm::mat3x3 GetMatrix() const;
		void Serialise(YAML::Emitter& out) const;
		static Transform Deserialise(const YAML::Node& node);
	};
}