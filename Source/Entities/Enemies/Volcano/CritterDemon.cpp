#include "CritterDemon.h"

const std::string CritterDemon::KeyEnemyCritterDemon = "critter_demon";

CritterDemon* CritterDemon::deserialize(ValueMap* initProperties)
{
	CritterDemon* instance = new CritterDemon(initProperties);

	instance->autorelease();

	return instance;
}

CritterDemon::CritterDemon(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Volcano_CritterDemon_Animations,
	false,
	Size(188.0f, 160.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

CritterDemon::~CritterDemon()
{
}
