#include "Vampiress1.h"

Vampiress1* Vampiress1::create()
{
	Vampiress1* instance = new Vampiress1();

	instance->autorelease();

	return instance;
}

Vampiress1::Vampiress1() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Vampiress1::~Vampiress1()
{
}
