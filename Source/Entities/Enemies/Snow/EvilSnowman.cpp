#include "EvilSnowman.h"

EvilSnowman* EvilSnowman::create()
{
	EvilSnowman* instance = new EvilSnowman();

	instance->autorelease();

	return instance;
}

EvilSnowman::EvilSnowman() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

EvilSnowman::~EvilSnowman()
{
}
