#include "pch.h"
#include "Entity.h"
#include "CoreSystem.h"
#include "yaml-cpp/yaml.h"

Spite::Entity::Entity() : Entity(Spite::core->GetNewID()) {}

Spite::Entity::Entity(std::uint32_t id) : position{ 0.0f, 0.0f }, scale{ 1.0f, 1.0f }, rotation{ 0.0f }, z{ 0.0f }, name{ "Entity" }, id{id} {}

void Spite::Entity::Update(double dt) {
    for (auto& c : components) {
        c->Update(dt);
    }
    for (auto& c : children) {
        c->Update(dt);
    }
}

void Spite::Entity::Draw(double dt) {
    for (auto& c : components) {
        c->Draw(dt);
    }
    for (auto& c : children) {
        c->Draw(dt);
    }
}

void Spite::Entity::Serialise(YAML::Emitter& out) const {
    out << YAML::Key << "Name" << YAML::Value << name;
    out << YAML::Key << "ID" << YAML::Value << id;
    out << YAML::Key << "Position" << YAML::Value << YAML::Flow << YAML::BeginSeq << position.x << position.y << YAML::EndSeq;
    out << YAML::Key << "Scale" << YAML::Value << YAML::Flow << YAML::BeginSeq << scale.x << scale.y << YAML::EndSeq;
    out << YAML::Key << "Rotation" << YAML::Value << rotation;
    out << YAML::Key << "Z" << YAML::Value << z;
    //Components
    out << YAML::Key << "Components";
    out << YAML::Value << YAML::BeginSeq;
    for (auto& c : components) {
        out << YAML::BeginMap;
        out << YAML::Key << "Name" << YAML::Value << c->GetName();
        c->Serialise(out);
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;
    //Children
    out << YAML::Key << "Children";
    out << YAML::Value << YAML::BeginSeq;
    for (auto& c : children) {
        out << YAML::BeginMap;
        c->Serialise(out);
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;
}

void Spite::Entity::Deserialise(const YAML::Node& node) {
    name = node["Name"].as<std::string>();
    id = node["ID"].as<std::uint32_t>();
    position.x = node["Position"][0].as<float>();
    position.y = node["Position"][1].as<float>();
    scale.x = node["Scale"][0].as<float>();
    scale.y = node["Scale"][1].as<float>();
    rotation = node["Rotation"].as<float>();
    z = node["Z"].as<float>();
    auto& comps = node["Components"];
    for (size_t i = 0, size = comps.size(); i < size; i++) {
        const YAML::Node& componentSubTree{ comps[i] };
        Spite::core->AddComponentByName(*this, componentSubTree["Name"].as<std::string>()).Deserialise(componentSubTree);
    }
    auto& childs = node["Children"];
    for (size_t i = 0, size = childs.size(); i < size; i++) {
        const YAML::Node& childSubTree{ childs[i] };
        auto* child = AddChild(std::make_unique<Spite::Entity>());
        child->Deserialise(childs[i]);
    }
}

const std::optional<Spite::Entity*>& Spite::Entity::GetParent() {
    return parent;
}

const std::vector<std::unique_ptr<Spite::Entity>>& Spite::Entity::GetChildren() {
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
