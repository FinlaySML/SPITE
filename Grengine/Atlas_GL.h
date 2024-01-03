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
		struct TextureInAtlas {
			glm::ivec2 offset;
			std::weak_ptr<Texture> tex;
		};
		std::optional<glm::vec2> FindFreeAtlasRegion(glm::vec2 dimensions);
		std::unordered_map<Texture*, TextureInAtlas> atlassed;
		std::shared_ptr<Texture_GL> texture;
		int atlasSize;
		int maxAtlasSize;
	};
}