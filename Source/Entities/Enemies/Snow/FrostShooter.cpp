#include "FrostShooter.h"

FrostShooter* FrostShooter::create()
{
	FrostShooter* instance = new FrostShooter();

	instance->autorelease();

	return instance;
}

FrostShooter::FrostShooter() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_FrostShooter_Animations,
	false)
{
}

FrostShooter::~FrostShooter()
{
}
