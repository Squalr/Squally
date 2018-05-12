#include "Jack.h"

Jack* Jack::create()
{
	Jack* instance = new Jack();

	instance->autorelease();

	return instance;
}

Jack::Jack() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Jack_Animations,
	false,
	Size(432.0f, 768.0f),
	0.25f,
	Vec2(0.0f, 0.0f))
{
}

Jack::~Jack()
{
}
