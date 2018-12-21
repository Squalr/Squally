////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Guard.h"

#include "Resources/EntityResources.h"

const std::string Guard::MapKeyGuard = "guard";

Guard* Guard::deserialize(cocos2d::ValueMap* initProperties)
{
	Guard* instance = new Guard(initProperties);

	instance->autorelease();

	return instance;
}

Guard::Guard(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_Guard_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Guard::~Guard()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
