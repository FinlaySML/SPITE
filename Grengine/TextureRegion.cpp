#include "pch.h"
#include "TextureRegion.h"
#include "Texture.h"
#include "RenderSystem.h"

Spite::TextureRegion::TextureRegion(std::shared_ptr<Texture> texture, glm::ivec2 origin, glm::ivec2 dimensions) : texture{texture}, origin{origin}, dimensions{dimensions} {
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
}

Spite::TextureRegion::TextureRegion(std::shared_ptr<Texture> texture) : TextureRegion{texture, {0,0}, texture->GetDimensions()} {}

void Spite::TextureRegion::Serialise(YAML::Emitter& out) const {
	out << YAML::Key << "Path" << YAML::Value << texture->Path().value_or("Unknown");
	out << YAML::Key << "Origin" << YAML::Value << YAML::Flow << YAML::BeginSeq << origin.x << origin.y << YAML::EndSeq;
	out << YAML::Key << "Dimensions" << YAML::Value << YAML::Flow << YAML::BeginSeq << dimensions.x << dimensions.y << YAML::EndSeq;
}

Spite::TextureRegion Spite::TextureRegion::Deserialise(const YAML::Node& node) {
	Spite::TextureRegion region{Spite::render->GetTexture(node["Path"].as<std::string>())};
	region.origin.x = node["Origin"][0].as<int>();
	region.origin.y = node["Origin"][1].as<int>();
	region.dimensions.x = node["Dimensions"][0].as<int>();
	region.dimensions.y = node["Dimensions"][1].as<int>();
	return region;
}
