#include "BlackWidow.h"

BlackWidow* BlackWidow::create()
{
	BlackWidow* instance = new BlackWidow();

	instance->autorelease();

	return instance;
}

BlackWidow::BlackWidow() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BlackWidow::~BlackWidow()
{
}
