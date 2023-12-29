#pragma once
#include "Scene.h"
#include "Entity.h"

class EntityFactories {
public:
	static std::unique_ptr<Spite::Entity> PlayerFactory(Spite::Scene* scene);
	static std::unique_ptr<Spite::Entity> EyeballFactory(Spite::Scene* scene, float health, float speed, float targetX, float offset);
	static std::unique_ptr<Spite::Entity> StarFactory(Spite::Scene* scene, float speed, float scale, float z);
	static std::unique_ptr<Spite::Entity> PlayerBulletFactory(Spite::Scene* scene);
	static std::unique_ptr<Spite::Entity> EnemyBulletFactory(Spite::Scene* scene);
};

