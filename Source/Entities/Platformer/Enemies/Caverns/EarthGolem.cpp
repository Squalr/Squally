#include "EarthGolem.h"

const std::string EarthGolem::KeyEnemyEarthGolem = "earth_golem";

EarthGolem* EarthGolem::deserialize(ValueMap* initProperties)
{
	EarthGolem* instance = new EarthGolem(initProperties);

	instance->autorelease();

	return instance;
}

EarthGolem::EarthGolem(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_EarthGolem_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 224.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

EarthGolem::~EarthGolem()
{
}
