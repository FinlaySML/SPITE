#pragma once
namespace Spite {
	class Texture;
	struct TextureRegion {
		TextureRegion(Texture* texture, glm::ivec2 origin, glm::ivec2 dimensions);
		TextureRegion(Texture* texture);
		Texture* texture;
		glm::ivec2 origin;
		glm::ivec2 dimensions;
	};
}
