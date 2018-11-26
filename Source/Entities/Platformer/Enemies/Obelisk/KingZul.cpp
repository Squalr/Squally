#include "KingZul.h"

const std::string KingZul::MapKeyEnemyKingZul = "king_zul";

KingZul* KingZul::deserialize(ValueMap* initProperties)
{
	KingZul* instance = new KingZul(initProperties);

	instance->autorelease();

	return instance;
}

KingZul::KingZul(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Obelisk_Enemies_KingZul_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(196.0f, 320.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

KingZul::~KingZul()
{
}
