#pragma once
#include "Scene.h"
#include "Entity.h"
#include "ManagerComponent.h"

class EntityFactory {
public:
	static std::unique_ptr<Spite::Entity> Wave(Spite::Scene* scene, ManagerComponent& manager);
	static std::unique_ptr<Spite::Entity> Player(Spite::Scene* scene, ManagerComponent& manager);
	static std::unique_ptr<Spite::Entity> UIHealth(Spite::Scene* scene);
	static std::unique_ptr<Spite::Entity> UIEndScreen(Spite::Scene* scene, bool won);
	static std::unique_ptr<Spite::Entity> Eyeball(Spite::Scene* scene, float targetX, float offset);
	static std::unique_ptr<Spite::Entity> EyeballSpray(Spite::Scene* scene, float targetX, float offset);
	static std::unique_ptr<Spite::Entity> EyeballSpin(Spite::Scene* scene, float targetX, float offset);
	static std::unique_ptr<Spite::Entity> EyeballMinimal(Spite::Scene* scene, float firingSpeed, float offset);
	static std::unique_ptr<Spite::Entity> EyeballWheel(Spite::Scene* scene, float targetX, float rotationSpeed = 0.1f, int eyeCount = 8, float radius = 1.4f, float firingSpeed = 1.5f, bool invert = false);
	static std::unique_ptr<Spite::Entity> Star(Spite::Scene* scene, float speed, float scale, float z);
	static std::unique_ptr<Spite::Entity> PlayerBullet(Spite::Scene* scene);
	static std::unique_ptr<Spite::Entity> EnemyBullet(Spite::Scene* scene, glm::vec2 velocity = { -10.0f, 0.0f });
};

