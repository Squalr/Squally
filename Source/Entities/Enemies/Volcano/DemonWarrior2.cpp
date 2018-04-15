#include "DemonWarrior2.h"

DemonWarrior2* DemonWarrior2::create()
{
	DemonWarrior2* instance = new DemonWarrior2();

	instance->autorelease();

	return instance;
}

DemonWarrior2::DemonWarrior2() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

DemonWarrior2::~DemonWarrior2()
{
}
