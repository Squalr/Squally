#include "DemonRogue.h"

DemonRogue* DemonRogue::create()
{
	DemonRogue* instance = new DemonRogue();

	instance->autorelease();

	return instance;
}

DemonRogue::DemonRogue() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

DemonRogue::~DemonRogue()
{
}
