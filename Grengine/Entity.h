#pragma once
#include "Component.h"

namespace Spite {
	class Entity
	{
	public:
		Entity();
		Entity(std::uint32_t id);
		Entity(Entity&) = delete;
		Entity& operator=(Entity&) = delete;
		Entity(Entity&&) = delete;
		Entity& operator=(Entity&&) = delete;
		void Update(double dt);
		void Draw(double dt);
		glm::vec2 position;
		glm::vec2 scale;
		float rotation;
		float z;
		std::string name;
		std::uint32_t id;
		//Serialisation
		void Serialise(YAML::Emitter&) const;
		static std::unique_ptr<Entity> Deserialise(const YAML::Node&);
		//Tree Management
		const std::optional<Entity*>& GetParent();
		const std::vector<std::unique_ptr<Entity>>& GetChildren();
		void MoveChild(Spite::Entity* child);
		Entity* AddChild(std::unique_ptr<Spite::Entity>&& child);
		std::unique_ptr<Spite::Entity> RemoveChild(Spite::Entity* child);
		//Component Management
		template <std::derived_from<Component> T>
		T& AddComponent() {
			T* component{ new T(*this) };
			components.emplace_back(component);
			return *component;
		}
		template <std::derived_from<Component> T>
		T& GetComponent() {
			for (auto& ptr : components) {
				if (typeid(*ptr.get()) == typeid(T)) {
					return *(T*)ptr.get();
				}
			}
			throw std::out_of_range{std::format("Cannot find component of type T where T={}", typeid(T).name())};
		}
		template <std::derived_from<Component> T>
		std::vector<T&> GetComponents() {
			std::vector<T&> vec;
			for (auto& c : components) {
				if (typeid(c.get()) == typeid(T)) {
					vec.push_back(*c);
				}
			}
			return vec;
		}
		void RemoveComponent(Component&);
	private:
		std::vector<std::unique_ptr<Component>> components;
		std::vector<std::unique_ptr<Entity>> children;
		std::optional<Entity*> parent;
	};

}