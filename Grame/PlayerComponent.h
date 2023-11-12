#pragma once
#include <Entity.h>

class PlayerComponent : public Spite::Component
{
public:
	PlayerComponent(Spite::Entity&);
	void Update(double dt) override;
	void Serialise(YAML::Emitter&) override;
	const std::string& GetName() override;
	static const std::string name;
};

