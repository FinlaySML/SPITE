#include "pch.h"
#include "Sprite.h"
#include "RenderSystem.h"

namespace Spite {
	Sprite::Sprite(Entity& entity) : Component(entity), colour{1,1,1,1} {
	}
	void Sprite::Draw(double dt) {
		Spite::render->GetDefaultSpriteBatch()->Add(*this);
	}
	const std::string Sprite::name = "SpriteComponent";
	const std::string& Sprite::GetName() {
		return name;
	}
	void Sprite::Serialise(YAML::Emitter& out) const {
		out << YAML::Key << "Colour" << YAML::Value << YAML::Flow << YAML::BeginSeq << colour.r << colour.g << colour.b << colour.a << YAML::EndSeq;
		if (textureRegion) {
			out << YAML::Key << "TextureRegion";
			out << YAML::Value << YAML::BeginMap;
			textureRegion->Serialise(out);
			out << YAML::EndMap;
		}
	}
	void Sprite::Deserialise(const YAML::Node& node) {
		colour.r = node["Colour"][0].as<float>();
		colour.g = node["Colour"][1].as<float>();
		colour.b = node["Colour"][2].as<float>();
		colour.a = node["Colour"][3].as<float>();
		if(node["TextureRegion"]) {
			textureRegion = TextureRegion::Deserialise(node["TextureRegion"]);
		}
	}
}