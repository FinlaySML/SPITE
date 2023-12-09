#pragma once
#include "Entity.h"
#include <vector>
#include <memory>
#include <unordered_map>

namespace Spite {
	class Scene
	{
		friend class Entity;
		friend class Component;
	public:
		Scene();
		void Update(float dt);
		void Draw();
		Entity* GetRoot();
		Entity* GetEntity(EntityID id);
		std::vector<Entity*> GetEntitiesByTag(const std::string& tag);
		std::vector<Entity*> GetEntitiesByName(const std::string& name);
		Component* GetComponent(ComponentID id);
		template <std::derived_from<Component> T> std::vector<T*> GetComponents();
		std::unique_ptr<Entity> CreateEntity();
		void Save(const std::filesystem::path& path);
		void Load(const std::filesystem::path& path);
	private:
		void AddEntity(Entity* entity);
		void RemoveEntity(EntityID id);
		void AddComponent(Component* component);
		void RemoveComponent(ComponentID id);
		std::unordered_map<EntityID, Entity*> entities;
		EntityID GetNewEntityID();
		EntityID usedEntityIds;
		std::unordered_map<ComponentID, Component*> components;
		ComponentID GetNewComponentID();
		ComponentID usedComponentIds;
		std::unique_ptr<Entity> root;
	};
	template <std::derived_from<Component> T>
	std::vector<T*> Scene::GetComponents() {
		std::vector<T*> result;
		for (auto& [id, component] : components) {
			if (typeid(*component) == typeid(T)) {
				result.push_back(component);
			}
		}
		return result;
	}
	template <std::derived_from<Component> T>
	T& Entity::AddComponent(std::optional<ComponentID> id) {
		T* component{ new T(this, id ? *id : scene->GetNewComponentID()) };
		components.emplace_back(component);
		return *component;
	}
}