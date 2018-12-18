////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Reaper.h"

#include "Resources/EntityResources.h"

const std::string Reaper::MapKeyReaper = "reaper";

Reaper* Reaper::deserialize(cocos2d::ValueMap* initProperties)
{
	Reaper* instance = new Reaper(initProperties);

	instance->autorelease();

	return instance;
}

Reaper::Reaper(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_Reaper_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(196.0f, 512.0f),
	0.8f,
	cocos2d::Vec2(0.0f, -128.0f))
{
}

Reaper::~Reaper()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
