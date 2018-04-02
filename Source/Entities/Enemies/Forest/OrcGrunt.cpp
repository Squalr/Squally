#include "OrcGrunt.h"

OrcGrunt* OrcGrunt::create()
{
	OrcGrunt* instance = new OrcGrunt();

	instance->autorelease();

	return instance;
}

OrcGrunt::OrcGrunt() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

OrcGrunt::~OrcGrunt()
{
}
