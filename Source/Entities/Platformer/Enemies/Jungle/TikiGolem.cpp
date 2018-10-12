#include "TikiGolem.h"

const std::string TikiGolem::MapKeyEnemyTikiGolem = "tiki_golem";

TikiGolem* TikiGolem::deserialize(ValueMap* initProperties)
{
	TikiGolem* instance = new TikiGolem(initProperties);

	instance->autorelease();

	return instance;
}

TikiGolem::TikiGolem(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_Enemies_TikiGolem_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(284.0f, 256.0f),
	1.0f,
	Vec2(0.0f, -112.0f))
{
}

TikiGolem::~TikiGolem()
{
}
