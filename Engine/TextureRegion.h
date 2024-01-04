#pragma once
#include "Texture.h"

namespace Spite {
	struct TextureRegion {
		TextureRegion(std::shared_ptr<Texture> texture, glm::ivec2 origin, glm::ivec2 dimensions);
		TextureRegion(std::shared_ptr<Texture> texture);
		std::shared_ptr<Texture> texture;
		glm::ivec2 origin;
		glm::ivec2 dimensions;
		void Serialise(YAML::Emitter&) const;
		static TextureRegion Deserialise(const YAML::Node&);
	};
}
