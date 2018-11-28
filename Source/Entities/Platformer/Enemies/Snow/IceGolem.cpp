#include "IceGolem.h"

const std::string IceGolem::MapKeyEnemyIceGolem = "ice_golem";

IceGolem* IceGolem::deserialize(ValueMap* initProperties)
{
	IceGolem* instance = new IceGolem(initProperties);

	instance->autorelease();

	return instance;
}

IceGolem::IceGolem(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Snow_Enemies_IceGolem_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(1680.0f, 996.0f),
	0.35f,
	Vec2(0.0f, 0.0f))
{
}

IceGolem::~IceGolem()
{
}
