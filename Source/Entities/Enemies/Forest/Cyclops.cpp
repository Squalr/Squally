#include "Cyclops.h"

Cyclops* Cyclops::create()
{
	Cyclops* instance = new Cyclops();

	instance->autorelease();

	return instance;
}

Cyclops::Cyclops() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

Cyclops::~Cyclops()
{
}
