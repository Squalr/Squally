////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "ZombieElric.h"

#include "Resources/EntityResources.h"

const std::string ZombieElric::MapKeyZombieElric = "zombie-elric";

ZombieElric* ZombieElric::deserialize(cocos2d::ValueMap* initProperties)
{
	ZombieElric* instance = new ZombieElric(initProperties);

	instance->autorelease();

	return instance;
}

ZombieElric::ZombieElric(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_ZombieElric_Animations,
	EntityResources::Enemies_CastleValgrind_ZombieElric_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(114.0f, 208.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

ZombieElric::~ZombieElric()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
