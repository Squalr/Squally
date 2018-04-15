#include "DemonWarrior.h"

DemonWarrior* DemonWarrior::create()
{
	DemonWarrior* instance = new DemonWarrior();

	instance->autorelease();

	return instance;
}

DemonWarrior::DemonWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

DemonWarrior::~DemonWarrior()
{
}
