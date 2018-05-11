#include "Jack.h"

Jack* Jack::create()
{
	Jack* instance = new Jack();

	instance->autorelease();

	return instance;
}

Jack::Jack() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Jack_Animations,
	false)
{
}

Jack::~Jack()
{
}
