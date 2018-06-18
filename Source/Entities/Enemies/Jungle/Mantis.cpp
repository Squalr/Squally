#include "Mantis.h"

const std::string Mantis::KeyEnemyMantis = "mantis";

Mantis* Mantis::create()
{
	Mantis* instance = new Mantis();

	instance->autorelease();

	return instance;
}

Mantis::Mantis() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_Mantis_Animations,
	false,
	Size(320.0f, 384.0f),
	0.75f,
	Vec2(-24.0f, 0.0f))
{
}

Mantis::~Mantis()
{
}
