#include "PigDemon.h"

PigDemon* PigDemon::create()
{
	PigDemon* instance = new PigDemon();

	instance->autorelease();

	return instance;
}

PigDemon::PigDemon() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_PigDemon_Animations,
	false)
{
}

PigDemon::~PigDemon()
{
}
