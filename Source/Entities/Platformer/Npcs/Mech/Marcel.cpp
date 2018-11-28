#include "Marcel.h"

const std::string Marcel::MapKeyNpcMarcel = "marcel";

Marcel* Marcel::deserialize(ValueMap* initProperties)
{
	Marcel* instance = new Marcel(initProperties);

	instance->autorelease();

	return instance;
}

Marcel::Marcel(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Mech_Npcs_Marcel_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Marcel::~Marcel()
{
}
