#include "Abomination.h"

const std::string Abomination::KeyEnemyAbomination = "abomination";

Abomination* Abomination::deserialize(ValueMap* initProperties)
{
	Abomination* instance = new Abomination(initProperties);

	instance->autorelease();

	return instance;
}

Abomination::Abomination(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Obelisk_Abomination_Animations,
	false,
	Size(296.0f, 356.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
}

Abomination::~Abomination()
{
}
