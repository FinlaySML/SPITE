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

const std::optional<Spite::Entity*>& Spite::Entity::GetParent()
{
    return parent;
}

const std::vector<std::unique_ptr<Spite::Entity>>& Spite::Entity::GetChildren()
{
    return children;
}

void Spite::Entity::AddChild(std::unique_ptr<Entity>&& child)
{
    if (child->parent; Entity* parent = *child->parent) {
        std::erase(parent->children, child);
    }
    if (std::ranges::find(children, [&](std::unique_ptr<Entity>& ptr) {return ptr.get() == child; }) != children.end()) {
        std::cout << "Could not add child because child already added" << std::endl;
        return;
    }
    child->parent = this;
    children.push_back(child);
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
