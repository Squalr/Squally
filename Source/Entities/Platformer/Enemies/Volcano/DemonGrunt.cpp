#include "DemonGrunt.h"

const std::string DemonGrunt::MapKeyEnemyDemonGrunt = "demon_grunt";

DemonGrunt* DemonGrunt::deserialize(ValueMap* initProperties)
{
	DemonGrunt* instance = new DemonGrunt(initProperties);

	instance->autorelease();

	return instance;
}

DemonGrunt::DemonGrunt(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Volcano_Enemies_DemonGrunt_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(312.0f, 372.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

DemonGrunt::~DemonGrunt()
{
}
