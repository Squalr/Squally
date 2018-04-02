#include "CritterDemon.h"

CritterDemon* CritterDemon::create()
{
	CritterDemon* instance = new CritterDemon();

	instance->autorelease();

	return instance;
}

CritterDemon::CritterDemon() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

CritterDemon::~CritterDemon()
{
}
