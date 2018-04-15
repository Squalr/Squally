#include "SkeletonPriestess.h"

SkeletonPriestess* SkeletonPriestess::create()
{
	SkeletonPriestess* instance = new SkeletonPriestess();

	instance->autorelease();

	return instance;
}

SkeletonPriestess::SkeletonPriestess() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

SkeletonPriestess::~SkeletonPriestess()
{
}
