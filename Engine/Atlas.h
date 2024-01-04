#pragma once
#include "Texture.h"
#include "TextureRegion.h"

namespace Spite {
	class Atlas {
	public:
		virtual ~Atlas() {};
		/// <summary>
		/// Converts a texture region so that it references a copy of the texture within the atlas rather than the original texture.
		/// Be wary of using this with very large/long textures as you may end up using lots of atlas space uneccesarily
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		virtual TextureRegion ConvertRegion(const TextureRegion&) = 0;
	};
}

