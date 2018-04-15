#include "AnubisWarrior.h"

AnubisWarrior* AnubisWarrior::create()
{
	AnubisWarrior* instance = new AnubisWarrior();

	instance->autorelease();

	return instance;
}

AnubisWarrior::AnubisWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

AnubisWarrior::~AnubisWarrior()
{
}
