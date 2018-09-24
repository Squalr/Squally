#include "BossDemonKing.h"

const std::string BossDemonKing::KeyEnemyBossDemonKing = "boss_demon_king";

BossDemonKing* BossDemonKing::deserialize(ValueMap* initProperties)
{
	BossDemonKing* instance = new BossDemonKing(initProperties);

	instance->autorelease();

	return instance;
}

BossDemonKing::BossDemonKing(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Volcano_Enemies_BossDemonKing_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(480.0f, 480.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

BossDemonKing::~BossDemonKing()
{
}
