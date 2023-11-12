#pragma once
#include "Subsystem.h"
#include "Component.h"
#include "Entity.h"
namespace Spite {
	class CoreSystem : public Subsystem {
	public:
		int Initialise() override;
		int Shutdown() override;
		void SaveScene(const Entity& root, const std::filesystem::path& path);
		std::unique_ptr<Entity> LoadScene(const std::filesystem::path& path);
		std::uint32_t GetNewID();
		Component& AddComponentByName(Entity& entity, const std::string& name);
		template <std::derived_from<Component> T>
		void Register() {
			std::string s = T::name;
			std::function<Spite::Component& (Spite::Entity&)> func = [](Spite::Entity& entity) -> Spite::Component& { return entity.AddComponent<T>(); };
			registeredComponents.insert({ s, func });
		};
	private:
		std::unordered_map<std::string, std::function<Component& (Entity&)>> registeredComponents;
		std::uint32_t usedIds{0};
	};
	extern CoreSystem* core;
}