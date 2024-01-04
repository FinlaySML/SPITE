#pragma once
#include "Subsystem.h"
#include "Component.h"
#include "Entity.h"
#include <typeinfo>
#include <typeindex>
namespace Spite {
	class CoreSystem : public Subsystem {
	public:
		int Initialise() override;
		int Shutdown() override;
		std::string GetName(Component* component);
		Component& AddComponentByName(Entity& entity, const std::string& name, ComponentID id);
		template <std::derived_from<Component> T>
		void Register(const std::string& name) {
			if(nameToFactory.contains(name)) {
				throw std::runtime_error(std::format("Could not set component name of '{}' to '{}', that name is already in use", typeid(T).name(), name));
			}
			auto index{ std::type_index(typeid(T)) };
			if (typeToName.contains(index)) {
				throw std::runtime_error(std::format("Can not register '{}', already registered", typeid(T).name()));
			}
			std::function<Spite::Component& (Spite::Entity&,ComponentID)> func = [](Spite::Entity& entity, ComponentID id) -> Spite::Component& { return entity.AddComponent<T>(id); };
			nameToFactory.insert({ name, func });
			typeToName.insert({ index, name });
		};
	private:
		std::unordered_map<std::string, std::function<Component& (Entity&,ComponentID)>> nameToFactory;
		std::unordered_map<std::type_index, std::string> typeToName;
	};
	extern CoreSystem* core;
}