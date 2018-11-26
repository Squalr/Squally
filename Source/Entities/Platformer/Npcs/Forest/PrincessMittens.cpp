#include "PrincessMittens.h"

const std::string PrincessMittens::MapKeyNpcPrincessMittens = "princess_mittens";

PrincessMittens* PrincessMittens::deserialize(ValueMap* initProperties)
{
	PrincessMittens* instance = new PrincessMittens(initProperties);

	instance->autorelease();

	return instance;
}

PrincessMittens::PrincessMittens(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Forest_Npcs_PrincessMittens_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

PrincessMittens::~PrincessMittens()
{
}
