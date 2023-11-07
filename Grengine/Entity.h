#pragma once
#include "Component.h"

namespace Spite {
	class Entity
	{
	public:
		Entity();
		void Update(double dt);
		void Draw(double dt);
		glm::vec2 position;
		glm::vec2 scale;
		float rotation;
		float z;
		//Component Management
		template <class T>
		T& AddComponent() {
			static_assert(std::is_base_of<Component, T>::value, "AddComponent<T>() requires T be derived from Component");
			T* component{ new T(*this) };
			components.emplace_back(component);
			return *component;
		}
		template <class T>
		T& GetComponent() {
			static_assert(std::is_base_of<Component, T>::value, "GetComponent<T>() requires T be derived from Component");
			for (auto& ptr : components) {
				if (typeid(*ptr.get()) == typeid(T)) {
					return *(T*)ptr.get();
				}
			}
			throw std::out_of_range{std::format("Cannot find component of type T where T={}", typeid(T).name())};
		}
		template <class T>
		std::vector<T&> GetComponents() {
			static_assert(std::is_base_of<Component, T>::value, "GetComponents<T>() requires T be derived from Component");
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
	};

}