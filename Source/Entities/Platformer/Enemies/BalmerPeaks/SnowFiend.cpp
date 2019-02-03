////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "SnowFiend.h"

#include "Resources/EntityResources.h"

const std::string SnowFiend::MapKeySnowFiend = "snow-fiend";

SnowFiend* SnowFiend::deserialize(cocos2d::ValueMap* initProperties)
{
	SnowFiend* instance = new SnowFiend(initProperties);

	instance->autorelease();

	return instance;
}

SnowFiend::SnowFiend(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_SnowFiend_Animations,
	EntityResources::Enemies_BalmerPeaks_SnowFiend_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(420.0f, 420.0f),
	0.7f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

SnowFiend::~SnowFiend()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
