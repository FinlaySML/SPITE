#include "pch.h"
#include "FunctionComponent.h"

Spite::FunctionComponent::FunctionComponent(Entity* parent, ComponentID id) : Component(parent, id) {}

void Spite::FunctionComponent::Update(float dt) {
	if(updateFunc) {
		updateFunc(this, dt);
	}
}