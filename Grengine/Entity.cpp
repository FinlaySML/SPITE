#include "pch.h"
#include "Entity.h"

Spite::Entity::Entity() : position{0.0f, 0.0f}, scale{ 1.0f, 1.0f }, rotation{ 0.0f }, z{0.0f}, name{"Entity"} {}

void Spite::Entity::Update(double dt)
{
    for (auto& c : components) {
        c->Update(dt);
    }
    for (auto& c : children) {
        c->Update(dt);
    }
}

void Spite::Entity::Draw(double dt)
{
    for (auto& c : components) {
        c->Draw(dt);
    }
    for (auto& c : children) {
        c->Draw(dt);
    }
}

const std::string& Spite::Entity::GetName() {
    return name;
}

void Spite::Entity::Serialise(YAML::Emitter& out) {
    out << YAML::Key << "Position" << YAML::Value << YAML::Flow << YAML::BeginSeq << position.x << position.y << YAML::EndSeq;
    out << YAML::Key << "Scale" << YAML::Value << YAML::Flow << YAML::BeginSeq << scale.x << scale.y << YAML::EndSeq;
    out << YAML::Key << "Rotation" << YAML::Value << rotation;
    out << YAML::Key << "Z" << YAML::Value << z;
    //Components
    out << YAML::Key << "Components";
    out << YAML::Value << YAML::BeginMap;
    for (auto& c : components) {
        out << YAML::Key << c->GetName();
        out << YAML::Value << YAML::BeginMap;
        c->Serialise(out);
        out << YAML::EndMap;
    }
    out << YAML::EndMap;
    //Children
    out << YAML::Key << "Children";
    out << YAML::Value << YAML::BeginMap;
    for (auto& c : children) {
        out << YAML::Key << c->GetName();
        out << YAML::Value << YAML::BeginMap;
        c->Serialise(out);
        out << YAML::EndMap;
    }
    out << YAML::EndMap;
}

void Spite::Entity::Deserialise(const YAML::Node&) {

}

const std::optional<Spite::Entity*>& Spite::Entity::GetParent()
{
    return parent;
}

const std::vector<std::unique_ptr<Spite::Entity>>& Spite::Entity::GetChildren()
{
    return children;
}

void Spite::Entity::MoveChild(Spite::Entity* child) {
    if (!child->parent) {
        throw new std::exception("Could not move child; does not have parent. Perhaps you meant to use AddChild(...) instead?");
    }
    Entity* oldParent = child->parent.value();
    if(oldParent == this) {
        throw new std::exception("Could not move child; already its parent.");
    }
    AddChild(oldParent->RemoveChild(child));
}

Spite::Entity* Spite::Entity::AddChild(std::unique_ptr<Spite::Entity>&& child) {
    if (child->parent) {
        throw new std::exception("Could not add child; it already has a parent. Perhaps you meant to use MoveChild(...) instead?");
    }
    child->parent = this;
    children.push_back(std::move(child));
    return children.back().get();
}

std::unique_ptr<Spite::Entity> Spite::Entity::RemoveChild(Spite::Entity* child) {
    auto it = std::find_if(children.begin(), children.end(), [=](const std::unique_ptr<Spite::Entity>& ptr) {return ptr.get() == child;});
    if(it == children.end()) {
        throw new std::exception("Could not find child to remove");
    }
    std::unique_ptr<Spite::Entity> entity{std::move(*it)};
    children.erase(it);
    return entity;
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
