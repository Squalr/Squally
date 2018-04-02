#include "BossWitch.h"

BossWitch* BossWitch::create()
{
	BossWitch* instance = new BossWitch();

	instance->autorelease();

	return instance;
}

BossWitch::BossWitch() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BossWitch::~BossWitch()
{
}
