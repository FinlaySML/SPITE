#pragma once
#include "Component.h"

namespace Spite {
	class Entity
	{
	public:
		void Update(double dt);
		void Draw(double dt);
		template <class T>
		T* AddComponent() {
			static_assert(std::is_base_of<Component, T>::value, "AddComponent<T>() requires T be derived from Component");
			T* component{ new T() };
			components.emplace_back(component);
			return component;
		}
		template <class T>
		T* GetComponent() {
			static_assert(std::is_base_of<Component, T>::value, "GetComponent<T>() requires T be derived from Component");
			for (auto& ptr : components) {
				if (typeid(ptr.get()) == typeid(T)) {
					return ptr.get();
				}
			}
			return nullptr;
		}
		template <class T>
		std::vector<T*> GetComponents() {
			static_assert(std::is_base_of<Component, T>::value, "GetComponents<T>() requires T be derived from Component");
			std::vector<T*> vec;
			for (auto& c : components) {
				if (typeid(c.get()) == typeid(T)) {
					vec.push_back(c.get());
				}
			}
			return vec;
		}
		void RemoveComponent(Component*);
		template <class T>
		static Entity* CreateWith() {
			static_assert(std::is_base_of<Component, T>::value, "CreateWith<T>() requires T be derived from Component");
			auto* e = new Entity();
			e->AddComponent<T>();
			return e;
		}
	private:
		std::vector<std::unique_ptr<Component>> components;
	};

}