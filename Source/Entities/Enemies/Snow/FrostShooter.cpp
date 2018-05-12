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
	Size(212.0f, 296.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

FrostShooter::~FrostShooter()
{
}
