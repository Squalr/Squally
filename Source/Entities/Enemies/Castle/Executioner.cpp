#include "Executioner.h"

const std::string Executioner::KeyEnemyExecutioner = "executioner";

Executioner* Executioner::create()
{
	Executioner* instance = new Executioner();

	instance->autorelease();

	return instance;
}

Executioner::Executioner() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Executioner_Animations,
	false,
	Size(472.0f, 820.0f),
	0.3f,
	Vec2(-24.0f, -410.0f))
{
}

Executioner::~Executioner()
{
}
