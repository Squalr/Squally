////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "VikingBot.h"

#include "Resources/EntityResources.h"

const std::string VikingBot::MapKeyVikingBot = "viking-bot";

VikingBot* VikingBot::deserialize(cocos2d::ValueMap* initProperties)
{
	VikingBot* instance = new VikingBot(initProperties);

	instance->autorelease();

	return instance;
}

VikingBot::VikingBot(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_VikingBot_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(768.0f, 960.0f),
	0.5f,
	cocos2d::Vec2(-332.0f, 0.0f),
	10,
	10)
{
}

VikingBot::~VikingBot()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
