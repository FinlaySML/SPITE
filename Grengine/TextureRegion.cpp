#include "pch.h"
#include "TextureRegion.h"
#include "Texture.h"

Spite::TextureRegion::TextureRegion(Texture* texture, glm::ivec2 origin, glm::ivec2 dimensions) {
	if(texture == nullptr) {
		std::cout << "Cannot create texture region, texture is nullptr" << std::endl;
		return;
	}
	if(!texture->IsLoaded()) {
		std::cout << "Cannot create texture region, texture is not loaded" << std::endl;
		return;
	}
	if(origin.x < 0 || origin.y < 0 || dimensions.x < 0 || dimensions.y < 0) {
		std::cout << "Cannot create texture region, origin or dimension have negative values" << std::endl;
		return;
	}
	auto tDim = texture->GetDimensions();
	if(dimensions.x + origin.x > tDim.x || dimensions.y + origin.y > tDim.y) {
		std::cout << "Cannot create texture region, origin plus dimension is greater than texture size" << std::endl;
		return;
	}
	this->texture = texture;
	this->origin = origin;
	this->dimensions = dimensions;
}

Spite::TextureRegion::TextureRegion(Texture* texture) : TextureRegion{texture, {0,0}, texture->GetDimensions()} {}
