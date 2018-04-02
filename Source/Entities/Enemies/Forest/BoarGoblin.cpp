#include "BoarGoblin.h"

BoarGoblin* BoarGoblin::create()
{
	BoarGoblin* instance = new BoarGoblin();

	instance->autorelease();

	return instance;
}

BoarGoblin::BoarGoblin() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BoarGoblin::~BoarGoblin()
{
}
