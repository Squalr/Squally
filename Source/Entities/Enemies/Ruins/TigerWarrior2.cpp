#include "TigerWarrior2.h"

TigerWarrior2* TigerWarrior2::create()
{
	TigerWarrior2* instance = new TigerWarrior2();

	instance->autorelease();

	return instance;
}

TigerWarrior2::TigerWarrior2() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

TigerWarrior2::~TigerWarrior2()
{
}
