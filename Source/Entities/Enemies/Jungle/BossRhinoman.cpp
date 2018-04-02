#include "BossRhinoman.h"

BossRhinoman* BossRhinoman::create()
{
	BossRhinoman* instance = new BossRhinoman();

	instance->autorelease();

	return instance;
}

BossRhinoman::BossRhinoman() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BossRhinoman::~BossRhinoman()
{
}
