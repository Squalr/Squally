#include "SkeletonCleaver.h"

SkeletonCleaver* SkeletonCleaver::create()
{
	SkeletonCleaver* instance = new SkeletonCleaver();

	instance->autorelease();

	return instance;
}

SkeletonCleaver::SkeletonCleaver() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

SkeletonCleaver::~SkeletonCleaver()
{
}
