#include "pch.h"
#include "Sprite.h"

namespace Spite {
	Sprite::Sprite(glm::vec2 position, float z) : position{ position }, scale{1,1}, rotation{0}, z{z} {
	}
	Sprite::Sprite() : Sprite({0,0}, 0) {
	}
}