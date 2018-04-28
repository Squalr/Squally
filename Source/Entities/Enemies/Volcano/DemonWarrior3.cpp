#include "DemonWarrior3.h"

DemonWarrior3* DemonWarrior3::create()
{
	DemonWarrior3* instance = new DemonWarrior3();

	instance->autorelease();

	return instance;
}

DemonWarrior3::DemonWarrior3() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

DemonWarrior3::~DemonWarrior3()
{
}
