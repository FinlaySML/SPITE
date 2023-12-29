#include "pch.h"
#include "AnimatorComponent.h"
#include "RenderSystem.h"
#include "Entity.h"
#include "Scene.h"

namespace Spite {
	AnimatorComponent::AnimatorComponent(Entity* parent, ComponentID id) : 
	Component(parent, id), 
	target{ 0 }, 
	frame{0},
	fps{10.0f},
	slices{1,1} {
	}
	
	void AnimatorComponent::Update(float dt) {
		if(!spriteSheet) {
			std::cout << "No Sprite Sheet found\n";
			return;
		}
		Spite::SpriteComponent* sprite{GetEntity()->GetScene()->GetComponent<Spite::SpriteComponent>(target)};
		if(sprite == nullptr) {
			std::cout << std::format("Could not find target component of id {}\n", target);
			return;
		}
		if(slices.x <= 0 || slices.y <= 0) {
			std::cout << std::format("Slice values must be greater than 0 ({},{})\n", slices.x, slices.y);
			return;
		}
		if(spriteSheet->dimensions % slices != glm::ivec2{0, 0}) {
			std::cout << std::format("Region dimensions must be divisible by slice: ({},{}) % ({},{}) = ({},{})\n", 
			spriteSheet->dimensions.x, spriteSheet->dimensions.y, 
			slices.x, slices.y,
			spriteSheet->dimensions.x % slices.x, spriteSheet->dimensions.y % slices.y);
			return;
		}
		int frameCount = slices.x * slices.y;
		frame = glm::mod<float>(frame + dt * fps, frameCount);
		glm::ivec2 regionDim{spriteSheet->dimensions / slices};
		glm::ivec2 regionOffset{regionDim.x * ((int)frame % slices.x), regionDim.y * ((int)frame / slices.x)};
		sprite->textureRegion = Spite::TextureRegion{spriteSheet->texture, spriteSheet->origin + regionOffset, regionDim};
	}

	void AnimatorComponent::Serialise(YAML::Emitter& out) const {
		out << YAML::Key << "Target";
		out << YAML::Value << target;
		out << YAML::Key << "SpriteSheet";
		if (spriteSheet) {
			out << YAML::Value << YAML::BeginMap;
			spriteSheet->Serialise(out);
			out << YAML::EndMap;
		} else {
			out << YAML::Value << "None";
		}
		out << YAML::Key << "Slices"; 
		out << YAML::Value << YAML::Flow << YAML::BeginSeq << slices.x << slices.y << YAML::EndSeq;
		out << YAML::Key << "Frame";
		out << YAML::Value << frame;
		out << YAML::Key << "FPS";
		out << YAML::Value << fps;
	}

	void AnimatorComponent::Deserialise(const YAML::Node& node) {
		target = node["Target"].as<decltype(target)>();
		if(node["SpriteSheet"].as<std::string>() != "None") {
			spriteSheet = TextureRegion::Deserialise(node["SpriteSheet"]);
		}
		slices.x = node["Slices"][0].as<decltype(slices.x)>();
		slices.y = node["Slices"][1].as<decltype(slices.y)>();
		frame = node["Frame"].as<decltype(frame)>();
		fps = node["FPS"].as<decltype(fps)>();
	}
}