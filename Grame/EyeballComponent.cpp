#include "EyeballComponent.h"
#include "Entity.h"
#include "AnimatorComponent.h"
#include "EntityFactories.h"
#include "RenderSystem.h"
#include "LivingComponent.h"

EyeballComponent::EyeballComponent(Spite::Entity* parent, Spite::ComponentID id) :
Component(parent, id),
attacked{false} {
}

void EyeballComponent::Update(float dt) {
	auto& cLiving{ GetEntity()->GetComponent<LivingComponent>() };
	auto& cAnimator{ GetEntity()->GetComponent<Spite::AnimatorComponent>() };
	cAnimator.spriteSheet = Spite::TextureRegion{ Spite::render->GetTexture("eyeball.png"), {0, cLiving.invulnerable ? 0 : 16}, {128, 16} };
	if(!cLiving.invulnerable) {
		if (0.5f < cAnimator.frame && cAnimator.frame < 1.0f) {
			if (!attacked) {
				attacked = true;
				auto bullet{ EntityFactories::EnemyBulletFactory(GetEntity()->GetScene()) };
				bullet->transform.position = GetEntity()->transform.position - glm::vec2{ 0.5f, 0.0f };
				GetEntity()->GetScene()->GetRoot()->AddChild(std::move(bullet));
			}
		} else {
			attacked = false;
		}
	}
}
