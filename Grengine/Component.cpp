#include "pch.h"
#include "Component.h"

Spite::Component::Component(Entity& entity) : parent{entity} {}

Spite::Component::~Component()
{
}

void Spite::Component::Update(double dt) {

}

void Spite::Component::Draw(double dt) {

}

Spite::Entity& Spite::Component::GetParent() const
{
    return parent;
}
