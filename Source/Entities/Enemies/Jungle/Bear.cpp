#include "Bear.h"

Bear* Bear::create()
{
	Bear* instance = new Bear();

	instance->autorelease();

	return instance;
}

Bear::Bear() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Bear::~Bear()
{
}
