#include "Beetle.h"

Beetle* Beetle::create()
{
	Beetle* instance = new Beetle();

	instance->autorelease();

	return instance;
}

Beetle::Beetle() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Beetle::~Beetle()
{
}
