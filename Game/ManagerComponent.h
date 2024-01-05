#pragma once
#include "Component.h"
#include "SoundHandle.h"
class ManagerComponent : public Spite::Component {
public:
	ManagerComponent(Spite::Entity* parent, Spite::ComponentID id);
	void Update(float dt) override;
	Spite::SoundHandle music;
	Spite::ComponentID waveComponentId;
	Spite::ComponentID playerComponentId;
};

