#include "EyeballComponent.h"
#include "Entity.h"
#include "AnimatorComponent.h"
#include "EntityFactory.h"
#include "RenderSystem.h"
#include "LivingComponent.h"

EyeballComponent::EyeballComponent(Spite::Entity* parent, Spite::ComponentID id) :
Component(parent, id),
bulletCountdown{0.0f},
bulletCooldownTime{1.0f} {
}

void EyeballComponent::Update(float dt) {
	auto& cLiving{ GetEntity()->GetComponent<LivingComponent>() };
	auto& cAnimator{ GetEntity()->GetComponent<Spite::AnimatorComponent>() };
	cAnimator.spriteSheet = Spite::TextureRegion{ Spite::render->GetTexture("eyeball.png"), {0, cLiving.invulnerable ? 0 : 16}, {128, 16} };
	bulletCountdown -= dt;
	if(bulletCountdown <= 0.0f) {
		bulletCountdown += bulletCooldownTime;
		if (!cLiving.invulnerable) {
			auto entity{GetEntity()};
			auto scene{entity->GetScene()};
			auto root{scene->GetRoot()};
			glm::vec2 begin{entity->TransformPoint(glm::vec2{0, 0}, root)};
			glm::vec2 end{entity->TransformPoint(glm::vec2{-0.5f, 0}, root)};
			auto bullet{ EntityFactory::EnemyBullet(scene, 6.0f * glm::normalize(end - begin)) };
			bullet->transform.position = end;
			root->AddChild(std::move(bullet));
		}
	}
}
