#include "BossKrampus.h"

BossKrampus* BossKrampus::create()
{
	BossKrampus* instance = new BossKrampus();

	instance->autorelease();

	return instance;
}

BossKrampus::BossKrampus() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BossKrampus::~BossKrampus()
{
}
