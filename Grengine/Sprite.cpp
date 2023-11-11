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
	const std::string& Sprite::GetComponentName() {
		return name;
	}
	void Sprite::Serialise(YAML::Emitter& out) {
		out << YAML::BeginMap;
		{
			out << YAML::Key << name;
			out << YAML::Value << YAML::BeginMap;
			{
				out << YAML::Key << "Colour" << YAML::Value << YAML::Flow << YAML::BeginSeq << colour.r << colour.g << colour.b << colour.a << YAML::EndSeq;
				if (textureRegion) {
					out << YAML::Key << "TextureRegion";
					out << YAML::Value;
					textureRegion->Serialise(out);
				}
			}
			out << YAML::EndMap;
		}
		out << YAML::EndMap;
	}
}