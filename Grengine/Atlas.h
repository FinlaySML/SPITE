#pragma once
#include "Texture.h"
#include "TextureRegion.h"

namespace Spite {
	class Atlas {
	public:
		virtual ~Atlas() {};
		virtual TextureRegion ConvertRegion(const TextureRegion&) = 0;
		virtual Texture* GetTexture() = 0;
	};
}

