#include "BossEvilEye.h"

BossEvilEye* BossEvilEye::create()
{
	BossEvilEye* instance = new BossEvilEye();

	instance->autorelease();

	return instance;
}

BossEvilEye::BossEvilEye() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BossEvilEye::~BossEvilEye()
{
}
