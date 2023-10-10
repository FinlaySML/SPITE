#pragma once
#include "Texture.h"
#include "Sprite.h"
namespace Spite {
	class SpriteBatch
	{
	public:
		virtual ~SpriteBatch();
		virtual void Add(const Sprite&) = 0;
		virtual void Draw() = 0;
	};
}

