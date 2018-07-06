#include "MechGolem.h"

const std::string MechGolem::KeyEnemyMechGolem = "mech_golem";

MechGolem* MechGolem::deserialize(ValueMap* initProperties)
{
	MechGolem* instance = new MechGolem(initProperties);

	instance->autorelease();

	return instance;
}

MechGolem::MechGolem(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Mech_MechGolem_Animations,
	false,
	Size(640.0f, 720.0f),
	0.7f,
	Vec2(-48.0f, 0.0f))
{
}

MechGolem::~MechGolem()
{
}
