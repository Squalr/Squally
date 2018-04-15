#include "Tiki.h"

Tiki* Tiki::create()
{
	Tiki* instance = new Tiki();

	instance->autorelease();

	return instance;
}

Tiki::Tiki() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Tiki::~Tiki()
{
}
