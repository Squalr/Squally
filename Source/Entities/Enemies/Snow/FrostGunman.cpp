#include "FrostGunman.h"

FrostGunman* FrostGunman::create()
{
	FrostGunman* instance = new FrostGunman();

	instance->autorelease();

	return instance;
}

FrostGunman::FrostGunman() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

FrostGunman::~FrostGunman()
{
}
