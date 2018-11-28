#include "PrincessMatu.h"

const std::string PrincessMatu::MapKeyNpcPrincessMatu = "princess_matu";

PrincessMatu* PrincessMatu::deserialize(ValueMap* initProperties)
{
	PrincessMatu* instance = new PrincessMatu(initProperties);

	instance->autorelease();

	return instance;
}

PrincessMatu::PrincessMatu(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Jungle_Npcs_PrincessMatu_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

PrincessMatu::~PrincessMatu()
{
}
