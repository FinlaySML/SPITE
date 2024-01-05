#include "pch.h"
#include "Component.h"
#include "Entity.h"
#include "Scene.h"

Spite::Component::Component(Entity* parent, ComponentID id) : entity{parent}, transform{}, id{id}, paused{PauseState::INHERIT} {
}

Spite::Component::~Component() {
}

void Spite::Component::Update(float dt) {
}

void Spite::Component::Draw(const glm::mat3x3& worldTransform) {
}

Spite::Entity* Spite::Component::GetEntity() const {
    return entity;
}

void Spite::Component::Serialise(YAML::Emitter& out) const {
}

void Spite::Component::Deserialise(const YAML::Node&) {
}
