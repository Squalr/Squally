#include "Abomination.h"

Abomination* Abomination::create()
{
	Abomination* instance = new Abomination();

	instance->autorelease();

	return instance;
}

Abomination::Abomination() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Abomination::~Abomination()
{
}
