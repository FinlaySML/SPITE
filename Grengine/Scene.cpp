#include "pch.h"
#include "Scene.h"

namespace Spite {
	Scene::Scene() : usedEntityIds{ 0 }, usedComponentIds{0}, root{ CreateEntity() } {
		root->name = "Root";
	}

	void Scene::Update(float dt) {
		root->Update(dt);
	}

	void Scene::Draw() {
		root->Draw(glm::mat3x3{1.0f});
	}

	Entity* Scene::GetRoot() {
		return root.get();
	}

	Entity* Scene::GetEntity(EntityID id) {
		auto it = entities.find(id);
		return it == entities.end() ? nullptr : it->second;
	}

	std::vector<Entity*> Scene::GetEntitiesByTag(const std::string& tag) {
		std::vector<Entity*> result;
		for(auto& [id, entity] : entities) {
			if(entity->HasTag(tag)) {
				result.push_back(entity);
			}
		}
		return result;
	}

	std::vector<Entity*> Scene::GetEntitiesByName(const std::string& name) {
		std::vector<Entity*> result;
		for (auto& [id, entity] : entities) {
			if (entity->name == name) {
				result.push_back(entity);
			}
		}
		return result;
	}

	Component* Scene::GetComponent(ComponentID id) {
		auto it = components.find(id);
		return it == components.end() ? nullptr : it->second;
	}

	std::unique_ptr<Entity> Scene::CreateEntity() {
		return std::make_unique<Entity>(this, GetNewEntityID());
	}

	void Scene::Save(const std::filesystem::path& path) {
		//Serialise
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "UsedEntityIDS" << YAML::Value << usedEntityIds;
		out << YAML::Key << "UsedComponentIDS" << YAML::Value << usedComponentIds;
		out << YAML::Key << "Root" << YAML::Value << YAML::BeginMap;
		root->Serialise(out);
		out << YAML::EndMap;
		out << YAML::EndMap;
		//Create directories
		if (auto parentPath = path.parent_path(); !parentPath.empty()) {
			std::filesystem::create_directories(parentPath);
		}
		//Save to file
		std::ofstream ofs(path);
		ofs << out.c_str();
		ofs.close();
	}

	void Scene::Load(const std::filesystem::path& path) {
		std::ifstream ofs(path);
		YAML::Node node = YAML::LoadFile(path.string());
		usedEntityIds = node["UsedEntityIDS"].as<decltype(usedEntityIds)>();
		usedEntityIds = node["UsedComponentIDS"].as<decltype(usedComponentIds)>();
		root = Spite::Entity::Deserialise(this, node["Root"]);
	}

	void Scene::AddEntity(Entity* entity) {
		entities.insert({entity->id, entity});
	}

	void Scene::RemoveEntity(EntityID id) {
		entities.erase(id);
	}

	void Scene::AddComponent(Component* component) {
		components.insert({ component->id, component });
	}

	void Scene::RemoveComponent(ComponentID id) {
		components.erase(id);
	}

	EntityID Scene::GetNewEntityID() {
		usedEntityIds++;
		return usedEntityIds;
	}
	ComponentID Scene::GetNewComponentID() {
		usedComponentIds++;
		return usedComponentIds;
	}
}
