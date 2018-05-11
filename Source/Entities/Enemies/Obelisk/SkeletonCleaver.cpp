#include "SkeletonCleaver.h"

SkeletonCleaver* SkeletonCleaver::create()
{
	SkeletonCleaver* instance = new SkeletonCleaver();

	instance->autorelease();

	return instance;
}

SkeletonCleaver::SkeletonCleaver() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_SkeletonCleaver_Animations,
	false)
{
}

SkeletonCleaver::~SkeletonCleaver()
{
}
