////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Troll.h"

#include "Resources/EntityResources.h"

const std::string Troll::MapKeyTroll = "troll";

Troll* Troll::deserialize(cocos2d::ValueMap* initProperties)
{
	Troll* instance = new Troll(initProperties);

	instance->autorelease();

	return instance;
}

Troll::Troll(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_Troll_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 248.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Troll::~Troll()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
