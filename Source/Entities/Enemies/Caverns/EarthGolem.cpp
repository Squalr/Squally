#include "EarthGolem.h"

EarthGolem* EarthGolem::create()
{
	EarthGolem* instance = new EarthGolem();

	instance->autorelease();

	return instance;
}

EarthGolem::EarthGolem() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

EarthGolem::~EarthGolem()
{
}
