#include "Ghost.h"

Ghost* Ghost::create()
{
	Ghost* instance = new Ghost();

	instance->autorelease();

	return instance;
}

Ghost::Ghost() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Ghost_Animations,
	false)
{
}

Ghost::~Ghost()
{
}
