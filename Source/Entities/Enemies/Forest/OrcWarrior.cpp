#include "OrcWarrior.h"

OrcWarrior* OrcWarrior::create()
{
	OrcWarrior* instance = new OrcWarrior();

	instance->autorelease();

	return instance;
}

OrcWarrior::OrcWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

OrcWarrior::~OrcWarrior()
{
}
