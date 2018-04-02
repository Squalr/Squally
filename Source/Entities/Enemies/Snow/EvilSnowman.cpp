#include "EvilSnowman.h"

EvilSnowman* EvilSnowman::create()
{
	EvilSnowman* instance = new EvilSnowman();

	instance->autorelease();

	return instance;
}

EvilSnowman::EvilSnowman() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

EvilSnowman::~EvilSnowman()
{
}
