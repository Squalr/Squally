#include "LightningGolem.h"

const std::string LightningGolem::MapKeyEnemyLightningGolem = "lightning_golem";

LightningGolem* LightningGolem::deserialize(ValueMap* initProperties)
{
	LightningGolem* instance = new LightningGolem(initProperties);

	instance->autorelease();

	return instance;
}

LightningGolem::LightningGolem(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Caverns_Enemies_LightningGolem_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(768.0f, 840.0f),
	0.30f,
	Vec2(0.0f, -420.0f))
{
}

LightningGolem::~LightningGolem()
{
}
