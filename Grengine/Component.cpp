#include "pch.h"
#include "Component.h"

Spite::Component::Component(Entity& entity) : parent{entity} {}

Spite::Component::~Component()
{
}

Spite::Entity& Spite::Component::GetParent() const
{
    return parent;
}
