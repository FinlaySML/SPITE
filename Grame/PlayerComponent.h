#pragma once
#include <Entity.h>

class PlayerComponent : public Spite::Component
{
	float bulletCooldown;
public:
	PlayerComponent(Spite::Entity* parent, Spite::ComponentID id);
	void Update(float dt) override;
};

