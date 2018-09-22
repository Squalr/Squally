#include "BlackWidow.h"

const std::string BlackWidow::KeyEnemyBlackWidow = "black_widow";

BlackWidow* BlackWidow::deserialize(ValueMap* initProperties)
{
	BlackWidow* instance = new BlackWidow(initProperties);

	instance->autorelease();

	return instance;
}

BlackWidow::BlackWidow(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_Enemies_BlackWidow_Animation,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(1280.0f, 920.0f),
	0.20f,
	Vec2(-112.0f, -396.0f))
{
}

BlackWidow::~BlackWidow()
{
}
