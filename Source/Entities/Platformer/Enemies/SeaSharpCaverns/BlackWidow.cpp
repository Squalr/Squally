////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "BlackWidow.h"

#include "Resources/EntityResources.h"

const std::string BlackWidow::MapKeyBlackWidow = "black-widow";

BlackWidow* BlackWidow::deserialize(cocos2d::ValueMap* initProperties)
{
	BlackWidow* instance = new BlackWidow(initProperties);

	instance->autorelease();

	return instance;
}

BlackWidow::BlackWidow(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_BlackWidow_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(1280.0f, 920.0f),
	0.20f,
	cocos2d::Vec2(-112.0f, 0.0f),
	10,
	10)
{
}

BlackWidow::~BlackWidow()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
