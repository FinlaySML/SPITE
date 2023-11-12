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
	if (glm::length(moveDir) > 0) {
		moveDir = glm::normalize(moveDir);
		GetParent().rotation = std::atan2(moveDir.x, moveDir.y);
	}
	moveDir *= 3.0f;
	GetParent().position += moveDir * dt;
	Spite::render->Camera().position = GetParent().position;
}

void PlayerComponent::Serialise(YAML::Emitter& out) const {
}

const std::string PlayerComponent::name = "PlayerComponent";

const std::string& PlayerComponent::GetName() {
	return name;
}
