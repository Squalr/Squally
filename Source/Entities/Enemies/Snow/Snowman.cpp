#include "Snowman.h"

Snowman* Snowman::create()
{
	Snowman* instance = new Snowman();

	instance->autorelease();

	return instance;
}

Snowman::Snowman() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

Snowman::~Snowman()
{
}
