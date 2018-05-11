#include "FrostDragon.h"

FrostDragon* FrostDragon::create()
{
	FrostDragon* instance = new FrostDragon();

	instance->autorelease();

	return instance;
}

FrostDragon::FrostDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_FrostDragon_Animations,
	false)
{
}

FrostDragon::~FrostDragon()
{
}
