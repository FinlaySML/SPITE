#include "WaveComponent.h"
#include "EntityFactory.h"

bool SpawnWave(Spite::Entity* parent, int waveNumber);

WaveComponent::WaveComponent(Spite::Entity* parent, Spite::ComponentID id) : Component(parent, id), currentWave{0}, finished{false} {
}

void WaveComponent::Update(float dt) {
	if(GetEntity()->GetChildCount() == 0) {
		if(SpawnWave(GetEntity(), currentWave)) {
			currentWave++;
		}else{
			finished = true;
		}
	}
}

bool SpawnWave(Spite::Entity* parent, int waveNumber) {
	auto* scene{parent->GetScene()};
	switch (waveNumber) {
	case 0:
	{
		auto eyeball0{ EntityFactory::Eyeball(scene, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactory::Eyeball(scene, 11.0f, 0.5f) };
		eyeball0->transform.position = { 24.0f, -3 };
		eyeball1->transform.position = { 24.0f, 3 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		break;
	}
	case 1:
	{
		auto eyeball0{ EntityFactory::Eyeball(scene, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactory::Eyeball(scene, 9.0f, 0.0f) };
		auto eyeball2{ EntityFactory::Eyeball(scene, 11.0f, 0.0f) };
		eyeball0->transform.position = { 24.0f, -5 };
		eyeball1->transform.position = { 24.0f, 0 };
		eyeball2->transform.position = { 24.0f, 5 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		parent->AddChild(std::move(eyeball2));
		break;
	}
	case 2:
	{
		auto eyeball0{ EntityFactory::Eyeball(scene, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactory::Eyeball(scene, 9.0f, 0.0f) };
		auto eyeball2{ EntityFactory::Eyeball(scene, 7.0f, 0.0f) };
		auto eyeball3{ EntityFactory::Eyeball(scene, 9.0f, 0.0f) };
		auto eyeball4{ EntityFactory::Eyeball(scene, 11.0f, 0.0f) };
		eyeball0->transform.position = { 24.0f, -5.0f };
		eyeball1->transform.position = { 24.0f, -2.5f };
		eyeball2->transform.position = { 24.0f, 0.0f };
		eyeball3->transform.position = { 24.0f, 2.5f };
		eyeball4->transform.position = { 24.0f, 5.0f };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		parent->AddChild(std::move(eyeball2));
		parent->AddChild(std::move(eyeball3));
		parent->AddChild(std::move(eyeball4));
		break;
	}
	case 3:
	{
		auto eyeball0{ EntityFactory::Eyeball(scene, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactory::EyeballSpray(scene, 9.0f, 0.0f) };
		auto eyeball2{ EntityFactory::Eyeball(scene, 11.0f, 0.0f) };
		eyeball0->transform.position = { 24.0f, -5 };
		eyeball1->transform.position = { 24.0f, 0 };
		eyeball2->transform.position = { 24.0f, 5 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		parent->AddChild(std::move(eyeball2));
		break;
	}
	case 4:
	{
		auto eyeball0{ EntityFactory::EyeballSpray(scene, 11.0f, 0.0f) };
		auto eyeball1{ EntityFactory::EyeballSpray(scene, 11.0f, 0.5f) };
		eyeball0->transform.position = { 24.0f, -3 };
		eyeball1->transform.position = { 24.0f, 3 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		break;
	}
	case 5:
	{
		auto eyeball0{ EntityFactory::EyeballWheel(scene, 9.0f) };
		eyeball0->transform.position = { 24.0f, 0 };
		parent->AddChild(std::move(eyeball0));
		break;
	}
	case 6:
	{
		auto eyeball0{ EntityFactory::EyeballWheel(scene, 9.0f, 0.1f, 12, 2.1f, 3.0f) };
		eyeball0->transform.position = { 24.0f, 0 };
		parent->AddChild(std::move(eyeball0));
		break;
	}
	case 7:
	{
		auto eyeball0{ EntityFactory::EyeballWheel(scene, 9.0f, 0.1f, 12, 2.1f, 3.0f, false) };
		auto eyeball1{ EntityFactory::EyeballWheel(scene, 9.0f, 0.1f, 12, 2.1f, 3.0f, true) };
		eyeball0->transform.position = { 24.0f, -4 };
		eyeball1->transform.position = { 24.0f, 4 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		break;
	}
	case 8:
	{
		auto eyeball0{ EntityFactory::EyeballWheel(scene, 9.0f, 0.1f, 6, 1.1f, 3.0f, false) };
		auto eyeball1{ EntityFactory::EyeballWheel(scene, 9.0f, 0.1f, 12, 2.1f, 3.0f, true) };
		auto eyeball2{ EntityFactory::EyeballWheel(scene, 9.0f, 0.1f, 18, 3.1f, 3.0f, false) };
		eyeball0->transform.position = { 28.0f, 0 };
		eyeball1->transform.position = { 28.0f, 0 };
		eyeball2->transform.position = { 28.0f, 0 };
		parent->AddChild(std::move(eyeball0));
		parent->AddChild(std::move(eyeball1));
		parent->AddChild(std::move(eyeball2));
		break;
	}
	default:{
		return false;
		break;
	}
	}
	return true;
}