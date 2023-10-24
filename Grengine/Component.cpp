#include "pch.h"
#include "Component.h"

Spite::Component::Component(Entity* parent) : parent{ parent }
{
}

Spite::Component::~Component()
{
}

Spite::Entity* Spite::Component::GetParent()
{
    return parent;
}
