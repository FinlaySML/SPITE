#pragma once
#include "Component.h"

class LivingComponent : public Spite::Component {
	float damageCooldown;
public:
	LivingComponent(Spite::Entity* parent, Spite::ComponentID id);
	void Update(float dt) override;
	void Hit(float damage);
	/// <summary>
	/// (LivingComponent* c, float damage, bool isDead)
	/// </summary>
	std::function<void(LivingComponent*, float, bool)> damageCallback;
	float maxHealth;
	float health;
	float hitRadius;
	float damageCooldownTime;
	float age;
	bool invulnerable;
};