#include "PigGoblin.h"

PigGoblin* PigGoblin::create()
{
	PigGoblin* instance = new PigGoblin();

	instance->autorelease();

	return instance;
}

PigGoblin::PigGoblin() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

PigGoblin::~PigGoblin()
{
}
