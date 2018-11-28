#include "Bodom.h"

const std::string Bodom::MapKeyNpcBodom = "bodom";

Bodom* Bodom::deserialize(ValueMap* initProperties)
{
	Bodom* instance = new Bodom(initProperties);

	instance->autorelease();

	return instance;
}

Bodom::Bodom(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Jungle_Npcs_Bodom_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Bodom::~Bodom()
{
}
