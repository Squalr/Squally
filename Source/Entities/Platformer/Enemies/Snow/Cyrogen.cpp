#include "Cyrogen.h"

const std::string Cyrogen::MapKeyEnemyCyrogen = "cyrogen";

Cyrogen* Cyrogen::deserialize(ValueMap* initProperties)
{
	Cyrogen* instance = new Cyrogen(initProperties);

	instance->autorelease();

	return instance;
}

Cyrogen::Cyrogen(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Snow_Enemies_Cryogen_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(420.0f, 420.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

Cyrogen::~Cyrogen()
{
}
