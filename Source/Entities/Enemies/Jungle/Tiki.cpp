#include "Tiki.h"

Tiki* Tiki::create()
{
	Tiki* instance = new Tiki();

	instance->autorelease();

	return instance;
}

Tiki::Tiki() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

Tiki::~Tiki()
{
}
