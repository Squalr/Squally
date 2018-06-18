#include "BossDragonOrcKing.h"

const std::string BossDragonOrcKing::KeyEnemyBossDragonOrcKing = "boss_dragon_orc_king";

BossDragonOrcKing* BossDragonOrcKing::deserialize(ValueMap* initProperties)
{
	BossDragonOrcKing* instance = new BossDragonOrcKing(initProperties);

	instance->autorelease();

	return instance;
}

BossDragonOrcKing::BossDragonOrcKing(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Forest_BossDragonOrcKing_Animations,
	false,
	Size(412.0f, 412.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

BossDragonOrcKing::~BossDragonOrcKing()
{
}
