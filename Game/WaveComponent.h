#pragma once
#include "Component.h"
class WaveComponent : public Spite::Component {
public:
	WaveComponent(Spite::Entity* parent, Spite::ComponentID id);
	void Update(float dt) override;
	int currentWave;
	bool finished;
};

