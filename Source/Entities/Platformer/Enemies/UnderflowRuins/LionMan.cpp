////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "LionMan.h"

#include "Resources/EntityResources.h"

const std::string LionMan::MapKeyLionMan = "lion-man";

LionMan* LionMan::deserialize(cocos2d::ValueMap* initProperties)
{
	LionMan* instance = new LionMan(initProperties);

	instance->autorelease();

	return instance;
}

LionMan::LionMan(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_LionMan_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 326.0f),
	1.0f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

LionMan::~LionMan()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
