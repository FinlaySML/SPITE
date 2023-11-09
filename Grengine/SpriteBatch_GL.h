#pragma once
#include "SpriteBatch.h"
#include "Atlas_GL.h"

namespace Spite {
	class RenderSystem_SDL;
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
			glm::vec3 transformRow0{ 1,0,0 }; float pad0;
			glm::vec3 transformRow1{ 0,1,0 }; float pad1;
			glm::vec3 transformRow2{ 0,0,1 }; float pad2;
			float z{ 0 }; float pad3{ 0 }; float pad4{ 0 }; float pad5{ 0 };
			glm::vec4 colour{ 1,1,1,1 };
			glm::vec2 uvOrigin{ 0,0 };
			glm::vec2 uvDimension{ 1,1 };
		};
		std::vector<ShaderSpriteData> spriteBatch;
		unsigned int ssbo;
		bool dataChanged;
	};
}
