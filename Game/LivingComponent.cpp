#include "LivingComponent.h"
#include "SpriteComponent.h"
#include "Entity.h"
#include "SoundSystem.h"

LivingComponent::LivingComponent(Spite::Entity* parent, Spite::ComponentID id) : 
Component(parent, id),
maxHealth{10.0f},
health{1.0f},
hitRadius{1.0f},
damageCooldownTime{0.15f},
damageCooldown{0.0f},
age{0.0f},
invulnerable{false} {
}

void LivingComponent::Update(float dt) {
	age += dt;
	auto sprites{GetEntity()->GetComponents<Spite::SpriteComponent>()};
	if(damageCooldown > 0) {
		damageCooldown -= dt;
		for(auto* s : sprites) {
			s->colour = damageCooldown > 0 ? glm::vec4{0.5, 0.5, 0.5, 1.0} : glm::vec4{1.0, 1.0, 1.0, 1.0};
		}
	}
}

void LivingComponent::Hit(float damage) {
	if(invulnerable) return;
	if(damageCooldown <= 0 || damage < 0.0f) {
		damageCooldown = damageCooldownTime;
		health = glm::clamp(health - damage, 0.0f, maxHealth);
		bool isDead{health == 0.0f};
		if (damageCallback) damageCallback(this, damage, isDead);
		auto* e{ GetEntity() };
		if (isDead) {
			e->GetParent()->RemoveChild(e);
		}
	}
}
