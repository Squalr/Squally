#include "Harpy.h"

const std::string Harpy::KeyEnemyHarpy = "harpy";

Harpy* Harpy::deserialize(ValueMap* initProperties)
{
	Harpy* instance = new Harpy(initProperties);

	instance->autorelease();

	return instance;
}

Harpy::Harpy(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Castle_Harpy_Animations,
	false,
	Size(172.0f, 256.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Harpy::~Harpy()
{
}
