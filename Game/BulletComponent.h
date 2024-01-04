#pragma once
#include "Entity.h"
class BulletComponent : public Spite::Component {
public:
	BulletComponent(Spite::Entity* parent, Spite::ComponentID id);
	void Update(float dt) override;
	glm::vec2 velocity;
	float damage;
	std::vector<std::string> targetTags;
};

