#include "Lion.h"

Lion* Lion::create()
{
	Lion* instance = new Lion();

	instance->autorelease();

	return instance;
}

Lion::Lion() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

Lion::~Lion()
{
}
