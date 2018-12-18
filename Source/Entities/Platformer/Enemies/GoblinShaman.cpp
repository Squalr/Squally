////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "GoblinShaman.h"

#include "Resources/EntityResources.h"

const std::string GoblinShaman::MapKeyGoblinShaman = "goblin-shaman";

GoblinShaman* GoblinShaman::deserialize(cocos2d::ValueMap* initProperties)
{
	GoblinShaman* instance = new GoblinShaman(initProperties);

	instance->autorelease();

	return instance;
}

GoblinShaman::GoblinShaman(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_GoblinShaman_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(96.0f, 204.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

GoblinShaman::~GoblinShaman()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
