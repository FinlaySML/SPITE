#include "EntityFactories.h"
#include "SpriteComponent.h"
#include "FunctionComponent.h"
#include "AnimatorComponent.h"
#include "LivingComponent.h"
#include "PlayerComponent.h"
#include "EyeballComponent.h"
#include "BulletComponent.h"
#include "FunctionComponent.h"
#include "RenderSystem.h"

std::unique_ptr<Spite::Entity> EntityFactories::StarFactory(Spite::Scene* scene, float speed, float scale, float z) {
	auto e = scene->CreateEntity();
	e->transform.position.x = (rand() / (float)RAND_MAX) * 32.0f - 16.0f;
	e->transform.position.y = (rand() / (float)RAND_MAX) * 18.0f - 9.0f;
	e->transform.rotation = (rand() / (float)RAND_MAX) * glm::two_pi<float>();
	e->transform.scale *= scale;
	e->z = z;
	auto& cSprite{ e->AddComponent<Spite::SpriteComponent>() };
	cSprite.textureRegion.emplace(Spite::render->GetTexture("star.png"));
	auto& cFunc{ e->AddComponent<Spite::FunctionComponent>() };
	cFunc.SetFunction([speed](Spite::FunctionComponent* c, float dt) {
		auto& x{ c->GetEntity()->transform.position.x };
		x -= dt * speed;
		if (x < -18.0f) {
			x = 18.0f;
		}
	});
	return e;
}

std::unique_ptr<Spite::Entity> EntityFactories::EyeballFactory(Spite::Scene* scene, float health, float speed, float targetX, float offset) {
	auto e{ scene->CreateEntity() };
	e->z = 2.0f;
	e->AddTag("enemy");
	auto& cSprite{ e->AddComponent<Spite::SpriteComponent>() };
	auto& cAnimator{ e->AddComponent<Spite::AnimatorComponent>() };
	cAnimator.slices.x = 8;
	cAnimator.target = cSprite.id;
	cAnimator.fps = 8.0f * speed;
	cAnimator.frame = 8.0f * offset;
	auto& cLiving{ e->AddComponent<LivingComponent>() };
	cLiving.hitRadius = 6.0f / 16.0f;
	cLiving.health = health;
	cLiving.invulnerable = true;
	auto& cEyeball{ e->AddComponent<EyeballComponent>() };
	auto& cFunc{ e->AddComponent<Spite::FunctionComponent>() };
	cFunc.SetFunction([=](Spite::FunctionComponent* c, float dt) {
		float& posX{ c->GetEntity()->transform.position.x };
		float step{ dt * speed * 5.0f };
		if (std::abs(posX - targetX) < step) {
			posX = targetX;
		} else if (posX > targetX) {
			posX -= step;
		} else if (posX < targetX) {
			posX += step;
		}
		if(posX == targetX) {
			auto& cLiving{ c->GetEntity()->GetComponent<LivingComponent>() };
			cLiving.invulnerable = false;
		}
	});
	//Make sure cAnimator has the spritesheet set
	cEyeball.Update(0.0f);
	return e;
}

std::unique_ptr<Spite::Entity> EntityFactories::PlayerFactory(Spite::Scene* scene) {
	auto e = scene->CreateEntity();
	e->z = 3.0f;
	e->AddTag("player");
	auto& cSprite{ e->AddComponent<Spite::SpriteComponent>() };
	cSprite.textureRegion.emplace(Spite::render->GetTexture("ship.png"));
	auto& cLiving{ e->AddComponent<LivingComponent>() };
	cLiving.health = 5.0f;
	cLiving.maxHealth = 5.0f;
	cLiving.hitRadius = 0.45f;
	auto& cPlayer{ e->AddComponent<PlayerComponent>() };
	return e;
}

std::unique_ptr<Spite::Entity> EntityFactories::PlayerBulletFactory(Spite::Scene* scene) {
	auto e{ scene->CreateEntity() };
	e->z = 1.0f;
	auto& sprite{ e->AddComponent<Spite::SpriteComponent>() };
	sprite.textureRegion.emplace(Spite::render->GetTexture("bullet.png"));
	sprite.transform.scale = { 6.0f / 16.0f, 6.0f / 16.0f };
	sprite.colour = { 0.5f, 0.5f, 1.0f, 1.0f };
	auto& bullet{ e->AddComponent<BulletComponent>() };
	bullet.velocity = { 10.0f, 0.0f };
	bullet.targetTags.push_back("enemy");
	return e;
}

std::unique_ptr<Spite::Entity> EntityFactories::EnemyBulletFactory(Spite::Scene* scene) {
	auto e{ scene->CreateEntity() };
	e->z = 1.0f;
	auto& sprite{ e->AddComponent<Spite::SpriteComponent>() };
	sprite.textureRegion.emplace(Spite::render->GetTexture("bullet.png"));
	sprite.transform.scale = { 6.0f / 16.0f, 6.0f / 16.0f };
	sprite.colour = { 1.0f, 0.5f, 0.5f, 1.0f };
	auto& bullet{ e->AddComponent<BulletComponent>() };
	bullet.velocity = { -10.0f, 0.0f };
	bullet.targetTags.push_back("player");
	return e;
}