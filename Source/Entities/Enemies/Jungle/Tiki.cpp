#include "Tiki.h"

Tiki* Tiki::create()
{
	Tiki* instance = new Tiki();

	instance->autorelease();

	return instance;
}

Tiki::Tiki() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Tiki::~Tiki()
{
}
