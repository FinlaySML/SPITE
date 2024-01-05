#include "EntityFactory.h"
#include "SpriteComponent.h"
#include "FunctionComponent.h"
#include "AnimatorComponent.h"
#include "LivingComponent.h"
#include "PlayerComponent.h"
#include "EyeballComponent.h"
#include "BulletComponent.h"
#include "FunctionComponent.h"
#include "RenderSystem.h"
#include "SoundSystem.h"
#include "WaveComponent.h"

//Layers
//[0,1) Background
//[1,2) Bullet
//[2,3) Enemy
//[3,4) Player

std::unique_ptr<Spite::Entity> EntityFactory::Star(Spite::Scene* scene, float speed, float scale, float z) {
	auto e = scene->CreateEntity();
	e->transform.position.x = (rand() / (float)RAND_MAX) * 33.0f - 16.5f;
	e->transform.position.y = (rand() / (float)RAND_MAX) * 18.0f - 9.0f;
	e->transform.rotation = (rand() / (float)RAND_MAX) * glm::two_pi<float>();
	e->transform.scale *= scale;
	e->z = z;
	auto& cSprite{ e->AddComponent<Spite::SpriteComponent>() };
	cSprite.textureRegion.emplace(Spite::render->GetTexture("star.png"));
	auto& cFunc{ e->AddComponent<Spite::FunctionComponent>() };
	cFunc.updateFunc = [speed](Spite::FunctionComponent* c, float dt) {
		auto& x{ c->GetEntity()->transform.position.x };
		x -= dt * speed;
		if (x < -16.5f) {
			x = 16.5f;
		}
	};
	return e;
}

void EnemyHitSoundEffect(LivingComponent* c, float damage, bool isDead) {
	Spite::sound->LoadSampleAndPlay("coin1.wav", 0.7f).Speed(2.0f);
}

std::unique_ptr<Spite::Entity> EntityFactory::Eyeball(Spite::Scene* scene, float targetX, float offset) {
	float speed{ 0.7f };
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
	cLiving.health = 5.0f;
	cLiving.maxHealth = 5.0f;
	cLiving.invulnerable = true;
	cLiving.damageCallback = EnemyHitSoundEffect;
	auto& cEyeball{ e->AddComponent<EyeballComponent>() };
	cEyeball.bulletCooldownTime = 1.0f / speed;
	cEyeball.bulletCountdown = offset / speed;
	auto& cFunc{ e->AddComponent<Spite::FunctionComponent>() };
	cFunc.updateFunc = [=](Spite::FunctionComponent* c, float dt) {
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
	};
	//Make sure cAnimator has the spritesheet set
	cEyeball.Update(0.0f);
	return e;
}

float TriangleWave(float x) {
	return 4.0f * std::abs(x - std::floor(x + 0.5f)) - 1.0f;
}

std::unique_ptr<Spite::Entity> EntityFactory::EyeballSpray(Spite::Scene* scene, float targetX, float offset) {
	float speed{ 0.7f };
	float rotationSpeed{ 0.5f };
	float firingTime{ 0.25f / rotationSpeed };
	auto e{ scene->CreateEntity() };
	e->z = 2.0f;
	e->AddTag("enemy");
	auto& cSprite{ e->AddComponent<Spite::SpriteComponent>() };
	auto& cAnimator{ e->AddComponent<Spite::AnimatorComponent>() };
	cAnimator.slices.x = 8;
	cAnimator.target = cSprite.id;
	cAnimator.fps = 8.0f / firingTime;
	auto& cLiving{ e->AddComponent<LivingComponent>() };
	cLiving.hitRadius = 6.0f / 16.0f;
	cLiving.health = 3.0f;
	cLiving.invulnerable = true;
	cLiving.damageCallback = EnemyHitSoundEffect;
	auto& cEyeball{ e->AddComponent<EyeballComponent>() };
	cEyeball.bulletCooldownTime = firingTime;
	cEyeball.bulletCountdown = offset / rotationSpeed;
	auto& cFunc{ e->AddComponent<Spite::FunctionComponent>() };
	cFunc.updateFunc = [=](Spite::FunctionComponent* c, float dt) {
		auto& cLiving{ c->GetEntity()->GetComponent<LivingComponent>() };
		float& posX{ c->GetEntity()->transform.position.x };
		float step{ dt * speed * 5.0f };
		if (std::abs(posX - targetX) < step) {
			posX = targetX;
		} else if (posX > targetX) {
			posX -= step;
		} else if (posX < targetX) {
			posX += step;
		}
		if (posX == targetX) {
			cLiving.invulnerable = false;
		}
		float& rot{ c->GetEntity()->transform.rotation };
		rot = TriangleWave(cLiving.age * rotationSpeed + offset) * 0.5f;
	};
	//Make sure cAnimator has the spritesheet set
	cEyeball.Update(0.0f);
	return e;
}

std::unique_ptr<Spite::Entity> EntityFactory::EyeballSpin(Spite::Scene* scene, float targetX, float offset) {
	float speed{ 0.7f };
	float rotationSpeed{ 0.25f };
	float firingSpeed{ 2.0f };
	auto e{ scene->CreateEntity() };
	e->z = 2.0f;
	e->AddTag("enemy");
	auto& cSprite{ e->AddComponent<Spite::SpriteComponent>() };
	auto& cAnimator{ e->AddComponent<Spite::AnimatorComponent>() };
	cAnimator.slices.x = 8;
	cAnimator.target = cSprite.id;
	cAnimator.fps = 8.0f * firingSpeed;
	auto& cLiving{ e->AddComponent<LivingComponent>() };
	cLiving.hitRadius = 6.0f / 16.0f;
	cLiving.health = 3.0f;
	cLiving.invulnerable = true;
	cLiving.damageCallback = EnemyHitSoundEffect;
	auto& cEyeball{ e->AddComponent<EyeballComponent>() };
	cEyeball.bulletCooldownTime = 1.0f / firingSpeed;
	cEyeball.bulletCountdown = 0.0f;
	auto& cFunc{ e->AddComponent<Spite::FunctionComponent>() };
	cFunc.updateFunc = [=](Spite::FunctionComponent* c, float dt) {
		auto& cLiving{ c->GetEntity()->GetComponent<LivingComponent>() };
		float& posX{ c->GetEntity()->transform.position.x };
		float step{ dt * speed * 5.0f };
		if (std::abs(posX - targetX) < step) {
			posX = targetX;
		} else if (posX > targetX) {
			posX -= step;
		} else if (posX < targetX) {
			posX += step;
		}
		if (posX == targetX) {
			cLiving.invulnerable = false;
		}
		float& rot{ c->GetEntity()->transform.rotation };
		rot = cLiving.age * rotationSpeed * glm::two_pi<float>();
	};
	//Make sure cAnimator has the spritesheet set
	cEyeball.Update(0.0f);
	return e;
}

std::unique_ptr<Spite::Entity> EntityFactory::EyeballMinimal(Spite::Scene* scene, float firingSpeed, float offset) {
	auto e{ scene->CreateEntity() };
	e->z = 2.0f;
	e->AddTag("enemy");
	auto& cSprite{ e->AddComponent<Spite::SpriteComponent>() };
	auto& cAnimator{ e->AddComponent<Spite::AnimatorComponent>() };
	cAnimator.slices.x = 8;
	cAnimator.target = cSprite.id;
	cAnimator.fps = 8.0f * firingSpeed;
	cAnimator.frame = 8.0f * offset;
	auto& cLiving{ e->AddComponent<LivingComponent>() };
	cLiving.hitRadius = 6.0f / 16.0f;
	cLiving.health = 3.0f;
	cLiving.invulnerable = true;
	cLiving.damageCallback = EnemyHitSoundEffect;
	auto& cEyeball{ e->AddComponent<EyeballComponent>() };
	cEyeball.bulletCooldownTime = 1.0f / firingSpeed;
	cEyeball.bulletCountdown = offset / firingSpeed;
	//Make sure cAnimator has the spritesheet set
	cEyeball.Update(0.0f);
	return e;
}

std::unique_ptr<Spite::Entity> EntityFactory::EyeballWheel(Spite::Scene* scene, float targetX, float rotationSpeed, int eyeCount, float radius, float firingSpeed, bool invert) {
	float speed{ 0.7f };
	auto base{ scene->CreateEntity() };
	auto& cFunc{ base->AddComponent<Spite::FunctionComponent>() };
	cFunc.updateFunc = [=](Spite::FunctionComponent* c, float dt) {
		auto* e{ c->GetEntity() };
		if(e->GetChildCount() == 0) {
			e->GetParent()->RemoveChild(e);
			return;
		}
		float& posX{ e->transform.position.x };
		float step{ dt * speed * 5.0f };
		if (std::abs(posX - targetX) < step) {
			posX = targetX;
		} else if (posX > targetX) {
			posX -= step;
		} else if (posX < targetX) {
			posX += step;
		}
		if (posX == targetX) {
			for(auto childID : e->GetChildren()) {
				if(Spite::Entity* child{e->GetScene()->GetEntity(childID)}) {
					auto& cLiving{child->GetComponent<LivingComponent>()};
					cLiving.invulnerable = false;
				}
			}
		}
		float& rot{ c->GetEntity()->transform.rotation };
		float rotationAmount{ rotationSpeed * glm::two_pi<float>() * dt };
		if (invert) rotationAmount = -rotationAmount;
		rot += rotationAmount;
	};
	//Create children
	for(int i{0}; i < eyeCount; i++) {
		float fraction{ i / (float)eyeCount };
		float angle{ fraction * glm::two_pi<float>()};
		auto eyeball{EntityFactory::EyeballMinimal(scene, firingSpeed, invert ? 1.0f - fraction : fraction)};
		eyeball->transform.rotation = angle;
		eyeball->transform.position = { -cos(angle) * radius, sin(angle) * radius };
		base->AddChild(std::move(eyeball));
	}
	return base;
}

std::unique_ptr<Spite::Entity> EntityFactory::Wave(Spite::Scene* scene, ManagerComponent& manager) {
	auto e{ scene->CreateEntity() };
	auto& cWave{ e->AddComponent<WaveComponent>() };
	manager.waveComponentId = cWave.id;
	return e;
}

std::unique_ptr<Spite::Entity> EntityFactory::Player(Spite::Scene* scene, ManagerComponent& manager) {
	auto e = scene->CreateEntity();
	e->z = 3.0f;
	e->AddTag("player");
	auto& cSprite{ e->AddComponent<Spite::SpriteComponent>() };
	cSprite.textureRegion.emplace(Spite::render->GetTexture("ship.png"));
	auto& cLiving{ e->AddComponent<LivingComponent>() };
	cLiving.health = 10.0f;
	cLiving.maxHealth = 10.0f;
	cLiving.hitRadius = 0.45f;
	cLiving.damageCooldownTime = 0.75f;
	cLiving.damageCallback = [](LivingComponent* c, float damage, bool dead) {
		Spite::sound->LoadSampleAndPlay("player_damage.wav");
	};
	auto& cPlayer{ e->AddComponent<PlayerComponent>() };
	manager.playerComponentId = cPlayer.id;
	return e;
}

std::unique_ptr<Spite::Entity> EntityFactory::UIHealth(Spite::Scene* scene) {
	auto e{scene->CreateEntity()};
	e->z = 10.0f;
	e->transform.position = {-15.5, 8.5};
	for(int i{0}; i < 10; i++) {
		auto& cSprite{e->AddComponent<Spite::SpriteComponent>()};
		cSprite.textureRegion.emplace(Spite::render->GetTexture("heart.png"));
		cSprite.transform.position.x = i;
		cSprite.transform.scale = {0.75f, 0.75f};
	}
	auto& cFunc{e->AddComponent<Spite::FunctionComponent>()};
	cFunc.updateFunc = [](Spite::FunctionComponent* c, float dt) {
		//Get the player
		for(Spite::Entity* player : c->GetEntity()->GetScene()->GetEntitiesByTag("player")) {
			auto& living{player->GetComponent<LivingComponent>()};
			//Iterate the heart sprites
			for(Spite::SpriteComponent* heart : c->GetEntity()->GetComponents<Spite::SpriteComponent>()) {
				if(heart->transform.position.x >= living.health) {
					heart->colour = { 0.25,0.25,0.25,1.0 };
				}else{
					heart->colour = { 1,1,1,1 };
				}
			}
		}
	};
	return e;
}

std::unique_ptr<Spite::Entity> EntityFactory::UIEndScreen(Spite::Scene* scene, bool won) {
	auto e{scene->CreateEntity()};
	e->z = 11.0f;
	e->AddTag("endscreen");
	auto& cSprite{e->AddComponent<Spite::SpriteComponent>()};
	cSprite.textureRegion = Spite::TextureRegion{Spite::render->GetTexture("endscreen.png"), {0,won ? 0 : 16}, {64, 16}};
	cSprite.transform.scale = {8, 2};
	return e;
}

std::unique_ptr<Spite::Entity> EntityFactory::PlayerBullet(Spite::Scene* scene) {
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

std::unique_ptr<Spite::Entity> EntityFactory::EnemyBullet(Spite::Scene* scene, glm::vec2 velocity) {
	auto e{ scene->CreateEntity() };
	e->z = 1.0f;
	auto& sprite{ e->AddComponent<Spite::SpriteComponent>() };
	sprite.textureRegion.emplace(Spite::render->GetTexture("bullet.png"));
	sprite.transform.scale = { 6.0f / 16.0f, 6.0f / 16.0f };
	sprite.colour = { 1.0f, 0.5f, 0.5f, 1.0f };
	auto& bullet{ e->AddComponent<BulletComponent>() };
	bullet.velocity = velocity;
	bullet.targetTags.push_back("player");
	return e;
}