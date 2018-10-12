#include "KingGrogg.h"

const std::string KingGrogg::MapKeyEnemyKingGrogg = "king_grogg";

KingGrogg* KingGrogg::deserialize(ValueMap* initProperties)
{
	KingGrogg* instance = new KingGrogg(initProperties);

	instance->autorelease();

	return instance;
}

KingGrogg::KingGrogg(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Forest_Enemies_KingGrogg_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(412.0f, 412.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

KingGrogg::~KingGrogg()
{
}
