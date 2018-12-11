#include "Santa.h"

const std::string Santa::MapKeyEnemySanta = "santa";

Santa* Santa::deserialize(ValueMap* initProperties)
{
	Santa* instance = new Santa(initProperties);

	instance->autorelease();

	return instance;
}

Santa::Santa(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Snow_Enemies_Santa_Animations,
	PlatformerCollisionType::Enemy,
	Size(420.0f, 452.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

Santa::~Santa()
{
}
