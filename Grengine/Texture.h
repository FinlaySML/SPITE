#pragma once
#include "pch.h"

namespace Spite {
	struct TextureRegion;
	class Texture {
	public:
		virtual ~Texture() {};
		virtual void LoadFromFile(const std::string& file) = 0;
		virtual void LoadFromData(std::span<unsigned char> data, unsigned x, unsigned y) = 0;
		virtual void Resize(glm::ivec2 newDimensions) = 0;
		virtual void Blit(const TextureRegion& source, glm::ivec2 destination) = 0;
		virtual bool IsLoaded() = 0;
		virtual glm::ivec2 GetDimensions() = 0;
	};
}

