#include "GoblinShaman.h"

GoblinShaman* GoblinShaman::create()
{
	GoblinShaman* instance = new GoblinShaman();

	instance->autorelease();

	return instance;
}

GoblinShaman::GoblinShaman() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

GoblinShaman::~GoblinShaman()
{
}
