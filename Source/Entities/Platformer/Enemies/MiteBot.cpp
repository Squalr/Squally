////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "MiteBot.h"

#include "Resources/EntityResources.h"

const std::string MiteBot::MapKeyMiteBot = "mite-bot";

MiteBot* MiteBot::deserialize(cocos2d::ValueMap* initProperties)
{
	MiteBot* instance = new MiteBot(initProperties);

	instance->autorelease();

	return instance;
}

MiteBot::MiteBot(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_MiteBot_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(420.0f, 296.0f),
	0.4f,
	cocos2d::Vec2(0.0f, 24.0f))
{
}

MiteBot::~MiteBot()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
