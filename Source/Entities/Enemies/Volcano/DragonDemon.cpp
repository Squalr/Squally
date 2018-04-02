#include "DragonDemon.h"

DragonDemon* DragonDemon::create()
{
	DragonDemon* instance = new DragonDemon();

	instance->autorelease();

	return instance;
}

DragonDemon::DragonDemon() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

DragonDemon::~DragonDemon()
{
}
