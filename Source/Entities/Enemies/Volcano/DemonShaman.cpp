#include "DemonShaman.h"

DemonShaman* DemonShaman::create()
{
	DemonShaman* instance = new DemonShaman();

	instance->autorelease();

	return instance;
}

DemonShaman::DemonShaman() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

DemonShaman::~DemonShaman()
{
}
