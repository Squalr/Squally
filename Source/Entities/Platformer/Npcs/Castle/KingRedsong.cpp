#include "KingRedsong.h"

const std::string KingRedsong::MapKeyNpcKingRedsong = "king_redsong";

KingRedsong* KingRedsong::deserialize(ValueMap* initProperties)
{
	KingRedsong* instance = new KingRedsong(initProperties);

	instance->autorelease();

	return instance;
}

KingRedsong::KingRedsong(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Npcs_KingRedsong_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

KingRedsong::~KingRedsong()
{
}
