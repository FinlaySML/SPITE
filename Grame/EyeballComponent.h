#pragma once
#include "Component.h"
class EyeballComponent : public Spite::Component {
public:
	EyeballComponent(Spite::Entity* parent, Spite::ComponentID id);
	void Update(float dt) override;
	float bulletCooldownTime;
	float bulletCountdown;
};

