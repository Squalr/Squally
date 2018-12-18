////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Agnes.h"

#include "Resources/EntityResources.h"

const std::string Agnes::MapKeyAgnes = "agnes";

Agnes* Agnes::deserialize(cocos2d::ValueMap* initProperties)
{
	Agnes* instance = new Agnes(initProperties);

	instance->autorelease();

	return instance;
}

Agnes::Agnes(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_Agnes_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(360.0f, 420.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Agnes::~Agnes()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
