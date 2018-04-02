#include "GoblinElf.h"

GoblinElf* GoblinElf::create()
{
	GoblinElf* instance = new GoblinElf();

	instance->autorelease();

	return instance;
}

GoblinElf::GoblinElf() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

GoblinElf::~GoblinElf()
{
}
