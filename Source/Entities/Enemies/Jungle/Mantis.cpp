#include "Mantis.h"

const std::string Mantis::KeyEnemyMantis = "mantis";

Mantis* Mantis::deserialize(ValueMap* initProperties)
{
	Mantis* instance = new Mantis(initProperties);

	instance->autorelease();

	return instance;
}

Mantis::Mantis(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_Mantis_Animations,
	false,
	Size(320.0f, 384.0f),
	0.75f,
	Vec2(-24.0f, 0.0f))
{
}

Mantis::~Mantis()
{
}
