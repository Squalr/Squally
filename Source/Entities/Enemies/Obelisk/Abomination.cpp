#include "Abomination.h"

const std::string Abomination::KeyEnemyAbomination = "abomination";

Abomination* Abomination::create()
{
	Abomination* instance = new Abomination();

	instance->autorelease();

	return instance;
}

Abomination::Abomination() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_Abomination_Animations,
	false,
	Size(296.0f, 356.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
}

Abomination::~Abomination()
{
}
