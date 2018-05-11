#include "Troll.h"

Troll* Troll::create()
{
	Troll* instance = new Troll();

	instance->autorelease();

	return instance;
}

Troll::Troll() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_Troll_Animations,
	false)
{
}

Troll::~Troll()
{
}
