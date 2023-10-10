#pragma once
#include "Texture.h"
#include "Sprite.h"
namespace Spite {
	class SpriteBatch
	{
	public:
		SpriteBatch(const Texture&);
		virtual void AddSprite(const Sprite&);
		virtual void Draw();
		SpriteBatch(SpriteBatch&) = delete;
		SpriteBatch& operator=(SpriteBatch&) = delete;
		virtual SpriteBatch(SpriteBatch&&);
		virtual SpriteBatch& operator=(SpriteBatch&&);
	};
}

