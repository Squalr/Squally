#include "Troll.h"

Troll* Troll::create()
{
	Troll* instance = new Troll();

	instance->autorelease();

	return instance;
}

Troll::Troll() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Troll::~Troll()
{
}
