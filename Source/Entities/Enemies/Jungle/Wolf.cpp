#include "Wolf.h"

Wolf* Wolf::create()
{
	Wolf* instance = new Wolf();

	instance->autorelease();

	return instance;
}

Wolf::Wolf() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Wolf::~Wolf()
{
}
