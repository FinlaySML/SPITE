#pragma once
#include "Entity.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <unordered_set>

namespace Spite {
	class Scene
	{
		friend class Entity;
		friend class Component;
	public:
		Scene();
		Scene(Scene&) = delete;
		Scene& operator=(Scene&) = delete;
		Scene(Scene&&) = delete;
		Scene& operator=(Scene&&) = delete;
		void Update(float dt);
		void Draw();
		Entity* GetRoot();
		Entity* GetEntity(EntityID id);
		const std::unordered_set<Entity*>& GetEntitiesByTag(const std::string& tag);
		std::vector<Entity*> GetEntitiesByName(const std::string& name);
		Component* GetComponent(ComponentID id);
		template <std::derived_from<Component> T> T* GetComponent(ComponentID id);
		template <std::derived_from<Component> T> const std::unordered_set<T*>& GetComponents();
		std::unique_ptr<Entity> CreateEntity();
		void Save(const std::filesystem::path& path);
		void Load(const std::filesystem::path& path);
		void Load(std::function<void(Scene&)> sceneProvider);
		void LoadDeferred(const std::filesystem::path& path);
		void LoadDeferred(std::function<void(Scene&)> sceneProvider);
		void Clear();
	private:
		void AddEntity(Entity* entity);
		void RemoveEntity(Entity* entity);
		void AddTag(Entity* entity, const std::string& tag);
		void RemoveTag(Entity* entity, const std::string& tag);
		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		std::unordered_map<EntityID, Entity*> entities;
		EntityID GetNewEntityID();
		EntityID usedEntityIds;
		std::unordered_map<ComponentID, Component*> components;
		std::unordered_map<std::type_index, std::unordered_set<Component*>> cachedComponentList;
		std::unordered_map<std::string, std::unordered_set<Entity*>> cachedTagList;
		ComponentID GetNewComponentID();
		ComponentID usedComponentIds;
		std::unique_ptr<Entity> root;
		bool inUpdate;
		std::optional<std::filesystem::path> loadDeferredPath;
		std::optional<std::function<void(Scene&)>> loadDeferredSceneProvider;
	};
	template <std::derived_from<Component> T>
	T* Scene::GetComponent(ComponentID id) {
		auto it = components.find(id);
		if(it == components.end()) return nullptr;
		if(typeid(*it->second) != typeid(T)) return nullptr;
		return (T*)it->second;
	}

	template <std::derived_from<Component> T>
	const std::unordered_set<T*>& Scene::GetComponents() {
		auto index{ std::type_index(typeid(T)) };
		return reinterpret_cast<const std::unordered_set<T*>&>(cachedComponentList[index]);
	}
	template <std::derived_from<Component> T>
	T& Entity::AddComponent(std::optional<ComponentID> id) {
		T* component{ new T(this, id ? *id : scene->GetNewComponentID()) };
		scene->AddComponent(component);
		components.emplace_back(component);
		return *component;
	}
}