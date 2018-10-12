#include "PrincessPepper.h"

const std::string PrincessPepper::MapKeyNpcPrincessPepper = "princess_pepper";

PrincessPepper* PrincessPepper::deserialize(ValueMap* initProperties)
{
	PrincessPepper* instance = new PrincessPepper(initProperties);

	instance->autorelease();

	return instance;
}

PrincessPepper::PrincessPepper(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Snow_Npcs_PrincessPepper_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

PrincessPepper::~PrincessPepper()
{
}
