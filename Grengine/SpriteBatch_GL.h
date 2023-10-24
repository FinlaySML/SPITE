#pragma once
#include "RenderSystem_SDL.h"
#include "SpriteBatch.h"
#include "Atlas_GL.h"

namespace Spite {
	class SpriteBatch_GL : public SpriteBatch {
	public:
		SpriteBatch_GL(RenderSystem_SDL*);
		~SpriteBatch_GL() final;
		void Add(const Sprite&) final;
		void Clear() final;
		void Draw() final;
	private:
		Atlas_GL atlas;
		RenderSystem_SDL* renderSystem;
		struct ShaderSpriteData {
			glm::vec2 translation{ 0,0 };
			glm::vec2 scale{ 1,1 };
			float rotation{ 0 };
			float z{ 0 };
			glm::vec2 padding{ 0, 0 };
			glm::vec2 uvOrigin{ 0,0 };
			glm::vec2 uvDimension{ 1,1 };
			glm::vec4 colour{ 1,1,1,1 };
		};
		std::vector<ShaderSpriteData> spriteBatch;
		unsigned int ssbo;
		bool dataChanged;
	};
}
