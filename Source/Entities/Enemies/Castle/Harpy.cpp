#include "Harpy.h"

Harpy* Harpy::create()
{
	Harpy* instance = new Harpy();

	instance->autorelease();

	return instance;
}

Harpy::Harpy() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Harpy::~Harpy()
{
}
