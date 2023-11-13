#include "pch.h"
#include "CoreSystem.h"
#include "Sprite.h"

Spite::CoreSystem* Spite::core = new Spite::CoreSystem();

int Spite::CoreSystem::Initialise() {
	Register<Spite::Sprite>();
	return 0;
}

int Spite::CoreSystem::Shutdown() {
	return 0;
}

void Spite::CoreSystem::SaveScene(const Spite::Entity& root, const std::filesystem::path& path) {
	//Serialise
	YAML::Emitter out;
	out << YAML::BeginMap;
	root.Serialise(out);
	out << YAML::EndMap;
	//Create directories
	if(auto parentPath = path.parent_path(); !parentPath.empty()) {
		std::filesystem::create_directories(parentPath);
	}
	//Save to file
	std::ofstream ofs(path);
	ofs << out.c_str();
	ofs.close();
}

std::unique_ptr<Spite::Entity> Spite::CoreSystem::LoadScene(const std::filesystem::path& path) {
	std::ifstream ofs(path);
	YAML::Node node = YAML::LoadFile(path.string());
	return Spite::Entity::Deserialise(node);
}

std::uint32_t Spite::CoreSystem::GetNewID() {
	usedIds++;
	return usedIds - 1;
}

Spite::Component& Spite::CoreSystem::AddComponentByName(Entity& entity, const std::string& name) {
	auto it = registeredComponents.find(name);
	if(it == registeredComponents.end()) {
		throw std::runtime_error(std::format("Could not add component '{}', perhaps it is not registered", name));
	}
	return it->second(entity);
}
