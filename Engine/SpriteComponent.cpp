#include "pch.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"

namespace Spite {
	SpriteComponent::SpriteComponent(Entity* parent, ComponentID id) : Component(parent, id), colour{1,1,1,1} {
	}
	void SpriteComponent::Draw(const glm::mat3x3& worldTransform) {
		Spite::render->GetDefaultSpriteBatch()->Add(worldTransform, *this);
	}
	void SpriteComponent::Serialise(YAML::Emitter& out) const {
		out << YAML::Key << "Colour" << YAML::Value << YAML::Flow << YAML::BeginSeq << colour.r << colour.g << colour.b << colour.a << YAML::EndSeq;
		out << YAML::Key << "TextureRegion";
		if (textureRegion) {
			out << YAML::Value << YAML::BeginMap;
			textureRegion->Serialise(out);
			out << YAML::EndMap;
		}else {
			out << YAML::Value << "None";
		}
	}
	void SpriteComponent::Deserialise(const YAML::Node& node) {
		colour.r = node["Colour"][0].as<float>();
		colour.g = node["Colour"][1].as<float>();
		colour.b = node["Colour"][2].as<float>();
		colour.a = node["Colour"][3].as<float>();
		if(node["TextureRegion"].as<std::string>() != "None") {
			textureRegion = TextureRegion::Deserialise(node["TextureRegion"]);
		}
	}
}