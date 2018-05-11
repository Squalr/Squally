#include "OrcGrunt.h"

OrcGrunt* OrcGrunt::create()
{
	OrcGrunt* instance = new OrcGrunt();

	instance->autorelease();

	return instance;
}

OrcGrunt::OrcGrunt() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_OrcGrunt_Animations,
	false)
{
}

OrcGrunt::~OrcGrunt()
{
}
