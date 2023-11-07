#include "pch.h"
#include "Sprite.h"

namespace Spite {
	Sprite::Sprite(Entity& entity) : Component(entity), colour{1,1,1,1} {
	}
	void Sprite::Update(double dt) {}
	void Sprite::Draw(double dt) {}
}