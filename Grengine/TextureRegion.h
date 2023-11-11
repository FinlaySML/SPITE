#pragma once
#include "Texture.h"
#include "Serialisable.h"

namespace Spite {
	struct TextureRegion : public Serialisable {
		TextureRegion(std::shared_ptr<Texture> texture, glm::ivec2 origin, glm::ivec2 dimensions);
		TextureRegion(std::shared_ptr<Texture> texture);
		std::shared_ptr<Texture> texture;
		glm::ivec2 origin;
		glm::ivec2 dimensions;
		void Serialise(YAML::Emitter&) override;
		void Deserialise(const YAML::Node&) override;
	};
}
