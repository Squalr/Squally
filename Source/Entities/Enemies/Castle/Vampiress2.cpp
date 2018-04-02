#include "Vampiress2.h"

Vampiress2* Vampiress2::create()
{
	Vampiress2* instance = new Vampiress2();

	instance->autorelease();

	return instance;
}

Vampiress2::Vampiress2() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Vampiress2::~Vampiress2()
{
}
