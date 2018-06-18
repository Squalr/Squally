#include "SkeletonCleaver.h"

const std::string SkeletonCleaver::KeyEnemySkeletonCleaver = "skeleton_cleaver";

SkeletonCleaver* SkeletonCleaver::create()
{
	SkeletonCleaver* instance = new SkeletonCleaver();

	instance->autorelease();

	return instance;
}

SkeletonCleaver::SkeletonCleaver() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_SkeletonCleaver_Animations,
	false,
	Size(128.0f, 312.0f),
	0.8f,
	Vec2(0.0f, 16.0f))
{
}

SkeletonCleaver::~SkeletonCleaver()
{
}
