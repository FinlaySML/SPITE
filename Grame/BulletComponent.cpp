#include "BulletComponent.h"
#include "Scene.h"
#include "LivingComponent.h"

BulletComponent::BulletComponent(Spite::Entity* parent, Spite::ComponentID id) : 
Component(parent, id), 
damage{1.0f},
velocity{0.0f, 0.0f} {
}

void BulletComponent::Update(float dt) {
	Spite::Entity* e{ GetEntity() };
	auto& p{e->transform.position};
	p += dt * velocity;
	if(p.x > 17.0f || p.x < -17.0f || p.y > 10.0f || p.y < -10.0f) {
		e->GetParent()->RemoveChild(e);
		return;
	}
	float minDistance{std::numeric_limits<float>::max()};
	LivingComponent* closestEnemy{nullptr};
	for(LivingComponent* ec : GetEntity()->GetScene()->GetComponents<LivingComponent>()) {
		bool hasTag{false};
		for(const std::string& tag : targetTags) {
			if(ec->GetEntity()->HasTag(tag)){
				hasTag = true;
				break;
			}
		}
		if(hasTag) {
			float distance{ glm::distance(ec->GetEntity()->TransformPoint({0,0}, GetEntity()), {0, 0})};
			if(distance < minDistance && distance < ec->hitRadius) {
				minDistance = distance;
				closestEnemy = ec;
			}
		}
	}
	if(closestEnemy) {
		closestEnemy->Hit(damage);
		e->GetParent()->RemoveChild(e);
	}
}
