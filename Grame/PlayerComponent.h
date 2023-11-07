#pragma once
#include <Entity.h>

class PlayerComponent : public Spite::Component
{
public:
	PlayerComponent(Spite::Entity&);
	void Update(double dt) override;
};

