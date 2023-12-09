#include "pch.h"
#include "Entity.h"
#include "CoreSystem.h"
#include "Scene.h"

Spite::Entity::Entity(Scene* scene, EntityID id) : z{ 0.0f }, name{ "Entity" }, id{id}, scene{ scene }, parent{nullptr} {
    scene->AddEntity(this);
}

Spite::Entity::~Entity() {
    scene->RemoveEntity(id);
}

void Spite::Entity::Update(float dt) {
    for (ComponentID cId : GetComponents()) {
        if(auto ptr = scene->GetComponent(cId)) {
            ptr->Update(dt);
        }
    }
    for(EntityID eId: GetChildren()) {
        auto ptr = scene->GetEntity(eId);
        if(ptr && ptr->GetParent() == this) {
            ptr->Update(dt);
        }
    }
}

void Spite::Entity::Draw(const glm::mat3x3& worldTransform) {
    glm::mat3x3 tf{worldTransform * transform.GetMatrix()};
    for (ComponentID c : GetComponents()) {
        if (auto ptr = scene->GetComponent(c)) {
            ptr->Draw(tf);
        }
    }
    for (EntityID e : GetChildren()) {
        auto ptr = scene->GetEntity(e);
        if (ptr && ptr->GetParent() == this) {
            ptr->Draw(tf);
        }
    }
}

bool Spite::Entity::AddTag(const std::string& tag) {
    if(!HasTag(tag)){
        tags.push_back(tag);
        return true;
    }
    return false;
}

bool Spite::Entity::HasTag(const std::string& tag) const {
    for(const std::string& t : tags) {
        if(t == tag) {
            return true;
        }
    }
    return false;
}

const std::vector<std::string>& Spite::Entity::GetTags() const {
    return tags;
}

void Spite::Entity::Serialise(YAML::Emitter& out) const {
    out << YAML::Key << "Name" << YAML::Value << name;
    out << YAML::Key << "ID" << YAML::Value << id;
    out << YAML::Key << "Transform" << YAML::Value << YAML::BeginMap;
    transform.Serialise(out);
    out << YAML::EndMap;
    out << YAML::Key << "Z" << YAML::Value << z;
    //Components
    out << YAML::Key << "Components";
    out << YAML::Value << YAML::BeginSeq;
    for (auto& c : components) {
        out << YAML::BeginMap;
        out << YAML::Key << "Name" << YAML::Value << Spite::core->GetName(c.get());
        out << YAML::Key << "ID" << YAML::Value << c->id;
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

std::unique_ptr<Spite::Entity> Spite::Entity::Deserialise(Scene* scene, const YAML::Node& node) {
    auto entity = std::make_unique<Spite::Entity>(scene, node["ID"].as<std::uint32_t>());
    entity->name = node["Name"].as<std::string>();
    entity->transform = Transform::Deserialise(node["Transform"]);
    entity->z = node["Z"].as<float>();
    auto& comps = node["Components"];
    for (size_t i = 0, size = comps.size(); i < size; i++) {
        Spite::core->AddComponentByName(*entity, comps[i]["Name"].as<std::string>(), comps[i]["ID"].as<ComponentID>()).Deserialise(comps[i]);
    }
    auto& childs = node["Children"];
    for (size_t i = 0, size = childs.size(); i < size; i++) {
        entity->AddChild(Entity::Deserialise(scene, childs[i]));
    }
    return entity;
}

Spite::Entity* Spite::Entity::GetParent() {
    return parent;
}

Spite::Scene* Spite::Entity::GetScene() {
    return scene;
}

std::vector<Spite::EntityID> Spite::Entity::GetChildren() const {
    std::vector<Spite::EntityID> result(children.size(), 0);
    for(size_t i{0}; i < children.size(); i++) {
        result[i] = children[i]->id;
    }
    return result;
}

std::vector<Spite::ComponentID> Spite::Entity::GetComponents() const {
    std::vector<Spite::ComponentID> result(components.size(), 0);
    for (size_t i{ 0 }; i < components.size(); i++) {
        result[i] = components[i]->id;
    }
    return result;
}

void Spite::Entity::MoveChild(Spite::Entity* child) {
    if (!child->parent) {
        throw new std::exception("Could not move child; does not have parent. Perhaps you meant to use AddChild(...) instead?");
    }
    if(child->parent == this) {
        throw new std::exception("Could not move child; already its parent.");
    }
    AddChild(child->parent->RemoveChild(child));
}

Spite::Entity* Spite::Entity::AddChild(std::unique_ptr<Spite::Entity>&& child) {
    if (child->parent) {
        throw new std::exception("Could not add child; it already has a parent. Perhaps you meant to use MoveChild(...) instead?");
    }
    if(child->scene != scene) {
        throw new std::exception("Cannot add or move a child from a different scene!");
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
