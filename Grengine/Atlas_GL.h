#pragma once
#include "Atlas.h"
#include "Texture_GL.h"
#include "TextureRegion.h"

namespace Spite {
	class Atlas_GL : public Atlas {
	public:
		Atlas_GL();
		~Atlas_GL();
		TextureRegion ConvertRegion(const TextureRegion&) final;
		unsigned int GetTextureGL();
	private:
		std::optional<glm::vec2> FindFreeAtlasRegion(glm::vec2 dimensions);
		std::unordered_map<Texture*, glm::ivec2> atlasOffsets;
		std::shared_ptr<Texture_GL> texture;
		unsigned int atlasSize;
	};
}