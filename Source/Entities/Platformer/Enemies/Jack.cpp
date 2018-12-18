////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Jack.h"

#include "Resources/EntityResources.h"

const std::string Jack::MapKeyJack = "jack";

Jack* Jack::deserialize(cocos2d::ValueMap* initProperties)
{
	Jack* instance = new Jack(initProperties);

	instance->autorelease();

	return instance;
}

Jack::Jack(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_Jack_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(432.0f, 768.0f),
	0.25f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Jack::~Jack()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
