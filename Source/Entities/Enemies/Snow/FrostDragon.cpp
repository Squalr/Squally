#include "FrostDragon.h"

FrostDragon* FrostDragon::create()
{
	FrostDragon* instance = new FrostDragon();

	instance->autorelease();

	return instance;
}

FrostDragon::FrostDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

FrostDragon::~FrostDragon()
{
}
