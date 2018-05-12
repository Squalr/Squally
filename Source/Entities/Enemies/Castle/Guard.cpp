#include "Guard.h"

Guard* Guard::create()
{
	Guard* instance = new Guard();

	instance->autorelease();

	return instance;
}

Guard::Guard() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Guard_Animations,
	false,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Guard::~Guard()
{
}
