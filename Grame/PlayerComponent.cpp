#include <pch.h>
#include "EventSystem.h"
#include "RenderSystem.h"
#include "PlayerComponent.h"
#include "FunctionComponent.h"
#include "Scene.h"
#include "SoundSystem.h"

PlayerComponent::PlayerComponent(Spite::Entity* entity, Spite::ComponentID id) : Component(entity, id), bulletCooldown{0} {
}

void PlayerComponent::Update(float dt) {
	//Movement
	glm::vec2 moveDir{ 0, 0 };
	if (Spite::event->IsPressed(Spite::KeyValue::KV_D)) {
		moveDir.x++;
	}
	if (Spite::event->IsPressed(Spite::KeyValue::KV_A)) {
		moveDir.x--;
	}
	if (Spite::event->IsPressed(Spite::KeyValue::KV_W)) {
		moveDir.y++;
	}
	if (Spite::event->IsPressed(Spite::KeyValue::KV_S)) {
		moveDir.y--;
	}
	moveDir *= glm::vec2{4.0f, 6.0f};
	auto minVal = Spite::render->Camera().position - Spite::render->Camera().dimensions * 0.5f;
	auto maxVal = Spite::render->Camera().position + Spite::render->Camera().dimensions * 0.5f;
	minVal.x += 0.5f;
	maxVal.x -= 0.5f;
	GetEntity()->transform.position = glm::clamp(GetEntity()->transform.position + moveDir * dt, minVal, maxVal);
	//Shooting
	if(bulletCooldown > 0) {
		bulletCooldown--;
	}else if(Spite::event->IsPressed(Spite::KeyLocation::KL_SPACE)) {
		bulletCooldown = 30;
		auto bullet{ GetEntity()->GetScene()->CreateEntity() };
		auto& sprite{ bullet->AddComponent<Spite::SpriteComponent>() };
		sprite.textureRegion.emplace(Spite::render->GetTexture("bullet.png"));
		sprite.transform.scale = {0.25f, 0.25f};
		auto& function{ bullet->AddComponent<Spite::FunctionComponent>() };
		function.SetFunction([](Spite::FunctionComponent* c, float dt) {
			auto* e{c->GetEntity()};
			e->transform.position.x += dt * 10.0f;
			if(e->transform.position.x > 0.0f) {
				e->GetParent()->RemoveChild(e);
			}
		});
		bullet->transform.position = GetEntity()->transform.position + glm::vec2{0.5f, 0.0f};
		GetEntity()->GetScene()->GetRoot()->AddChild(std::move(bullet));
		Spite::sound->LoadSampleAndPlay("coin1.wav", 1.0f).Speed(2.5f);
	}
}