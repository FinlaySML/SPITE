#include <pch.h>
#include "EventSystem.h"
#include "RenderSystem.h"
#include "PlayerComponent.h"

PlayerComponent::PlayerComponent(Spite::Entity& entity) : Component{entity}
{
}

void PlayerComponent::Update(double dt)
{
	glm::vec2 moveDir{ 0, 0 };
	if (Spite::event->IsPressed(Spite::KeyValue::KV_D)) {
		moveDir.x++;
	}
	if (Spite::event->IsPressed(Spite::KeyValue::KV_A)) {
		moveDir.x--;
	}
	if (Spite::event->IsPressed(Spite::KeyValue::KV_W)) {
		moveDir.y++;
	}
	if (Spite::event->IsPressed(Spite::KeyValue::KV_S)) {
		moveDir.y--;
	}
	/*if (glm::length(moveDir) > 0) {
		moveDir = glm::normalize(moveDir);
		GetParent().rotation = std::atan2(moveDir.x, moveDir.y);
	}*/
	moveDir *= glm::vec2{7.0f, 4.0f};
	auto minVal = Spite::render->Camera().position - Spite::render->Camera().dimensions * 0.5f;
	auto maxVal = Spite::render->Camera().position + Spite::render->Camera().dimensions * 0.5f;
	GetParent().position = glm::clamp(GetParent().position + moveDir * dt, minVal, maxVal);
}

void PlayerComponent::Serialise(YAML::Emitter& out) const {
}

const std::string PlayerComponent::name = "PlayerComponent";

const std::string& PlayerComponent::GetName() {
	return name;
}
