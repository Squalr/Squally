#include "BossGoddess.h"

BossGoddess* BossGoddess::create()
{
	BossGoddess* instance = new BossGoddess();

	instance->autorelease();

	return instance;
}

BossGoddess::BossGoddess() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BossGoddess::~BossGoddess()
{
}
