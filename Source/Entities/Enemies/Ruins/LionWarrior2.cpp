#include "LionWarrior2.h"

LionWarrior2* LionWarrior2::create()
{
	LionWarrior2* instance = new LionWarrior2();

	instance->autorelease();

	return instance;
}

LionWarrior2::LionWarrior2() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

LionWarrior2::~LionWarrior2()
{
}
