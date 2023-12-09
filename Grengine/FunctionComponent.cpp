#include "pch.h"
#include "FunctionComponent.h"

Spite::FunctionComponent::FunctionComponent(Entity* parent, ComponentID id) : Component(parent, id) {}

void Spite::FunctionComponent::Update(float dt) {
	f(this, dt);
}

void Spite::FunctionComponent::SetFunction(const std::function<void(FunctionComponent*,double)>& function) {
	f = function;
}
