#include "PigDemon.h"

PigDemon* PigDemon::create()
{
	PigDemon* instance = new PigDemon();

	instance->autorelease();

	return instance;
}

PigDemon::PigDemon() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_PigDemon_Animations,
	false,
	Size(256.0f, 240.0f),
	0.8f,
	Vec2(-64.0f, -32.0f))
{
}

PigDemon::~PigDemon()
{
}
