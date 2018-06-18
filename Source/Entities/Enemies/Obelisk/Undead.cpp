#include "Undead.h"

const std::string Undead::KeyEnemyUndead = "undead";

Undead* Undead::create()
{
	Undead* instance = new Undead();

	instance->autorelease();

	return instance;
}

Undead::Undead() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_Undead_Animations,
	false,
	Size(146.0f, 248.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Undead::~Undead()
{
}
