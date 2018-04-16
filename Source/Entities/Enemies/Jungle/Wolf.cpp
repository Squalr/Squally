#include "Wolf.h"

Wolf* Wolf::create()
{
	Wolf* instance = new Wolf();

	instance->autorelease();

	return instance;
}

Wolf::Wolf() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Wolf::~Wolf()
{
}
