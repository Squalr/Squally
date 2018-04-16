#include "Skeleton.h"

Skeleton* Skeleton::create()
{
	Skeleton* instance = new Skeleton();

	instance->autorelease();

	return instance;
}

Skeleton::Skeleton() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Skeleton::~Skeleton()
{
}
