#include "FrostGunman.h"

FrostGunman* FrostGunman::create()
{
	FrostGunman* instance = new FrostGunman();

	instance->autorelease();

	return instance;
}

FrostGunman::FrostGunman() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

FrostGunman::~FrostGunman()
{
}
