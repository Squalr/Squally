#include "PigDemon.h"

PigDemon* PigDemon::create()
{
	PigDemon* instance = new PigDemon();

	instance->autorelease();

	return instance;
}

PigDemon::PigDemon() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

PigDemon::~PigDemon()
{
}
