////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Roger.h"

#include "Resources/EntityResources.h"

const std::string Roger::MapKeyRoger = "roger";

Roger* Roger::deserialize(cocos2d::ValueMap* initProperties)
{
	Roger* instance = new Roger(initProperties);

	instance->autorelease();

	return instance;
}

Roger::Roger(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_LambdaCrypts_Roger_Animations,
	EntityResources::Npcs_LambdaCrypts_Roger_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Roger::~Roger()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
