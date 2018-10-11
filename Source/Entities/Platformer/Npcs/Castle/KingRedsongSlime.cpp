#include "KingRedsongSlime.h"

const std::string KingRedsongSlime::KeyEnemyKingRedsongSlime = "king_redsong_slime";

KingRedsongSlime* KingRedsongSlime::deserialize(ValueMap* initProperties)
{
	KingRedsongSlime* instance = new KingRedsongSlime(initProperties);

	instance->autorelease();

	return instance;
}

KingRedsongSlime::KingRedsongSlime(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Npcs_KingRedsongSlime_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

KingRedsongSlime::~KingRedsongSlime()
{
}
