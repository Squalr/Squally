#include "Undead.h"

Undead* Undead::create()
{
	Undead* instance = new Undead();

	instance->autorelease();

	return instance;
}

Undead::Undead() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

Undead::~Undead()
{
}
