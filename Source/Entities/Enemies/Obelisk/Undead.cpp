#include "Undead.h"

Undead* Undead::create()
{
	Undead* instance = new Undead();

	instance->autorelease();

	return instance;
}

Undead::Undead() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Undead::~Undead()
{
}
