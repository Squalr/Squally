#include "Troll.h"

Troll* Troll::create()
{
	Troll* instance = new Troll();

	instance->autorelease();

	return instance;
}

Troll::Troll() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_Troll_Animations,
	false,
	Size(256.0f, 248.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Troll::~Troll()
{
}
