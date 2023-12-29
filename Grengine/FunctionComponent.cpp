#include "pch.h"
#include "FunctionComponent.h"

Spite::FunctionComponent::FunctionComponent(Entity* parent, ComponentID id) : Component(parent, id) {}

void Spite::FunctionComponent::Update(float dt) {
	if(f) {
		f(this, dt);
	}
}

void Spite::FunctionComponent::SetFunction(const std::function<void(FunctionComponent*,float)>& function) {
	f = function;
}
