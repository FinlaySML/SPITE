#pragma once
#include "Texture.h"
#include "SpriteComponent.h"
namespace Spite {
	class SpriteBatch
	{
	public:
		virtual ~SpriteBatch() {};
		virtual void Add(const glm::mat3x3& worldTransform, const SpriteComponent& sprite) = 0;
		virtual void Clear() = 0;
		virtual void Draw() = 0;
	};
}

