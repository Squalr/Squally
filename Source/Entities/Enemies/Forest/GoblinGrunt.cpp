#include "GoblinGrunt.h"

GoblinGrunt* GoblinGrunt::create()
{
	GoblinGrunt* instance = new GoblinGrunt();

	instance->autorelease();

	return instance;
}

GoblinGrunt::GoblinGrunt() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

GoblinGrunt::~GoblinGrunt()
{
}
