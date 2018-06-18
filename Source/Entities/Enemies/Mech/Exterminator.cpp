#include "Exterminator.h"

const std::string Exterminator::KeyEnemyExterminator = "exterminator";

Exterminator* Exterminator::create()
{
	Exterminator* instance = new Exterminator();

	instance->autorelease();

	return instance;
}

Exterminator::Exterminator() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_Exterminator_Animations,
	false,
	Size(320.0f, 278.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Exterminator::~Exterminator()
{
}
