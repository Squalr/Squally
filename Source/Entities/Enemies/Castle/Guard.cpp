#include "Guard.h"

Guard* Guard::create()
{
	Guard* instance = new Guard();

	instance->autorelease();

	return instance;
}

Guard::Guard() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Guard_Animations,
	false)
{
}

Guard::~Guard()
{
}
