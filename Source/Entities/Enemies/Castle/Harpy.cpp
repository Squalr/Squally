#include "Harpy.h"

const std::string Harpy::KeyEnemyHarpy = "harpy";

Harpy* Harpy::create()
{
	Harpy* instance = new Harpy();

	instance->autorelease();

	return instance;
}

Harpy::Harpy() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Harpy_Animations,
	false,
	Size(172.0f, 256.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Harpy::~Harpy()
{
}
