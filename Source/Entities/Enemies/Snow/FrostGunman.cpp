#include "FrostGunman.h"

FrostGunman* FrostGunman::create()
{
	FrostGunman* instance = new FrostGunman();

	instance->autorelease();

	return instance;
}

FrostGunman::FrostGunman() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

FrostGunman::~FrostGunman()
{
}
