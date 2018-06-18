#include "GoblinGrunt.h"

const std::string GoblinGrunt::KeyEnemyGoblinGrunt = "goblin_grunt";

GoblinGrunt* GoblinGrunt::deserialize(ValueMap* initProperties)
{
	GoblinGrunt* instance = new GoblinGrunt(initProperties);

	instance->autorelease();

	return instance;
}

GoblinGrunt::GoblinGrunt(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Jungle_GoblinGrunt_Animations,
	false,
	Size(312.0f, 512.0f),
	0.35f,
	Vec2(0.0f, -224.0f))
{
}

GoblinGrunt::~GoblinGrunt()
{
}
