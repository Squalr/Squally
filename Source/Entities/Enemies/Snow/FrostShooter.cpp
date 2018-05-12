#include "FrostShooter.h"

FrostShooter* FrostShooter::create()
{
	FrostShooter* instance = new FrostShooter();

	instance->autorelease();

	return instance;
}

FrostShooter::FrostShooter() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_FrostShooter_Animations,
	false,
	Size(240.0f, 312.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

FrostShooter::~FrostShooter()
{
}
