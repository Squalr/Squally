#include "Reindeer.h"

Reindeer* Reindeer::create()
{
	Reindeer* instance = new Reindeer();

	instance->autorelease();

	return instance;
}

Reindeer::Reindeer() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

Reindeer::~Reindeer()
{
}
