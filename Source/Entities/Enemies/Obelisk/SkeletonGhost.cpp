#include "SkeletonGhost.h"

SkeletonGhost* SkeletonGhost::create()
{
	SkeletonGhost* instance = new SkeletonGhost();

	instance->autorelease();

	return instance;
}

SkeletonGhost::SkeletonGhost() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

SkeletonGhost::~SkeletonGhost()
{
}
