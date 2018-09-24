#include "BossDragonOrcKing.h"

const std::string BossDragonOrcKing::KeyEnemyBossDragonOrcKing = "boss_dragon_orc_king";

BossDragonOrcKing* BossDragonOrcKing::deserialize(ValueMap* initProperties)
{
	BossDragonOrcKing* instance = new BossDragonOrcKing(initProperties);

	instance->autorelease();

	return instance;
}

BossDragonOrcKing::BossDragonOrcKing(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Forest_Enemies_BossDragonOrcKing_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(412.0f, 412.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

BossDragonOrcKing::~BossDragonOrcKing()
{
}
