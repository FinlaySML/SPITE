#pragma once
#include "Component.h"
#include "Transform.h"
#include "PauseState.h"
#include <iosfwd>
namespace Spite {
	class Scene;
	using EntityID = std::uint32_t;
	class Entity
	{
		friend class Scene;
	private:
		std::vector<std::unique_ptr<Component>> components;
		std::vector<std::string> tags;
		std::vector<std::unique_ptr<Entity>> children;
		Entity* parent;
		Scene* scene;
		int depth;
		EntityID id;
		EntityID rootId;
		void SetDepthAndRootID(int newDepth, EntityID newRootID);
	public:
		Entity(Scene* scene, EntityID id);
		~Entity();
		Entity(Entity&) = delete;
		Entity& operator=(Entity&) = delete;
		Entity(Entity&&) = delete;
		Entity& operator=(Entity&&) = delete;
		void Update(float dt, bool parentPaused);
		void Draw(const glm::mat3x3& worldTransform);
		Transform transform;
		float z;
		std::string name;
		PauseState paused;
		//ID
		int GetDepth() const;
		EntityID GetID() const;
		EntityID GetRootID() const;
		//Tags
		bool AddTag(const std::string&);
		bool HasTag(const std::string&) const;
		const std::vector<std::string>& GetTags() const;
		//Serialisation
		void Serialise(YAML::Emitter&) const;
		static std::unique_ptr<Entity> Deserialise(Scene* scene, const YAML::Node&);
		//Tree Management
		Entity* GetParent();
		Scene* GetScene();
		std::vector<EntityID> GetChildren() const;
		size_t GetChildCount() const;
		std::vector<ComponentID> GetComponents() const;
		void MoveChild(Spite::Entity* child );
		Entity* AddChild(std::unique_ptr<Spite::Entity>&& child);
		std::unique_ptr<Spite::Entity> RemoveChild(Spite::Entity* child);
		//Transform
		glm::vec2 TransformPoint(glm::vec2 point, Entity* target);
		//Component Management
		template <std::derived_from<Component> T> T& AddComponent(std::optional<ComponentID> id = {});
		template <std::derived_from<Component> T> T& GetComponent();
		template <std::derived_from<Component> T> std::vector<T*> GetComponents();
		void RemoveComponent(Component&);
	};
	template <std::derived_from<Component> T>
	T& Entity::GetComponent() {
		for (auto& ptr : components) {
			if (typeid(*ptr.get()) == typeid(T)) {
				return *(T*)ptr.get();
			}
		}
		throw std::out_of_range{ std::format("Cannot find component of type T where T={}", typeid(T).name()) };
	}
	template <std::derived_from<Component> T>
	std::vector<T*> Entity::GetComponents() {
		std::vector<T*> vec;
		for (auto& c : components) {
			if (typeid(*c.get()) == typeid(T)) {
				vec.push_back((T*)c.get());
			}
		}
		return vec;
	}
}
