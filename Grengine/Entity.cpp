#include "pch.h"
#include "Entity.h"

void Spite::Entity::Update(double dt)
{
    for (auto& c : components) {
        c->Update(dt);
    }
}

void Spite::Entity::Draw(double dt)
{
    for (auto& c : components) {
        c->Draw(dt);
    }
}

void Spite::Entity::RemoveComponent(Component* toRemove)
{
    for (auto it = components.begin(); it != components.end(); ++it) {
        if (it->get() == toRemove) {
            components.erase(it);
            break;
        }
    }
}
