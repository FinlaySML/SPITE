#include "pch.h"
#include "CoreSystem.h"
#include "SpriteComponent.h"
#include "FunctionComponent.h"
#include "AnimatorComponent.h"

Spite::CoreSystem* Spite::core = new Spite::CoreSystem();

int Spite::CoreSystem::Initialise() {
	Register<Spite::SpriteComponent>("SpriteComponent");
	Register<Spite::FunctionComponent>("FunctionComponent");
	Register<Spite::AnimatorComponent>("AnimatorComponent");
	return 0;
}

int Spite::CoreSystem::Shutdown() {
	return 0;
}

std::string Spite::CoreSystem::GetName(Component* component) {
	auto it{typeToName.find(std::type_index(typeid(*component)))};
	if (it == typeToName.end()) {
		throw std::runtime_error(std::format("Could not GetName(...) of component '{}', perhaps it is not registered", typeid(*component).name()));
	}
	return it->second;
}

Spite::Component& Spite::CoreSystem::AddComponentByName(Entity& entity, const std::string& name, ComponentID id) {
	auto it = nameToFactory.find(name);
	if(it == nameToFactory.end()) {
		throw std::runtime_error(std::format("Could not add component '{}', perhaps it is not registered", name));
	}
	return it->second(entity, id);
}
