#include "pch.h"
#include "Entity.h"

Spite::Entity::Entity() : position{0.0f, 0.0f}, scale{ 1.0f, 1.0f }, rotation{ 0.0f }, z{0.0f} {}

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

void Spite::Entity::RemoveComponent(Component& toRemove)
{
    for (auto it = components.begin(); it != components.end(); ++it) {
        if (it->get() == &toRemove) {
            components.erase(it);
            break;
        }
    }
}
