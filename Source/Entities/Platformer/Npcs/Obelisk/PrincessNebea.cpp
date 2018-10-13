#include "PrincessNebea.h"

const std::string PrincessNebea::MapKeyNpcPrincessNebea = "princess_nebea";

PrincessNebea* PrincessNebea::deserialize(ValueMap* initProperties)
{
	PrincessNebea* instance = new PrincessNebea(initProperties);

	instance->autorelease();

	return instance;
}

PrincessNebea::PrincessNebea(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_PrincessNebea_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

PrincessNebea::~PrincessNebea()
{
}
