#include "MechGuard.h"

const std::string MechGuard::KeyEnemyMechGuard = "mech_guard";

MechGuard* MechGuard::deserialize(ValueMap* initProperties)
{
	MechGuard* instance = new MechGuard(initProperties);

	instance->autorelease();

	return instance;
}

MechGuard::MechGuard(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Mech_Enemies_MechGuard_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 596.0f),
	0.3f,
	Vec2(-24.0f, -298.0f))
{
}

MechGuard::~MechGuard()
{
}
