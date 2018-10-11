#include "PrincessOpal.h"

const std::string PrincessOpal::KeyEnemyPrincessOpal = "princess_opal";

PrincessOpal* PrincessOpal::deserialize(ValueMap* initProperties)
{
	PrincessOpal* instance = new PrincessOpal(initProperties);

	instance->autorelease();

	return instance;
}

PrincessOpal::PrincessOpal(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Npcs_PrincessOpal_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

PrincessOpal::~PrincessOpal()
{
}
