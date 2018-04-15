#include "LionWarrior.h"

LionWarrior* LionWarrior::create()
{
	LionWarrior* instance = new LionWarrior();

	instance->autorelease();

	return instance;
}

LionWarrior::LionWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

LionWarrior::~LionWarrior()
{
}
