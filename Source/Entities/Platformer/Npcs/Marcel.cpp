////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Marcel.h"

#include "Resources/EntityResources.h"

const std::string Marcel::MapKeyMarcel = "marcel";

Marcel* Marcel::deserialize(cocos2d::ValueMap* initProperties)
{
	Marcel* instance = new Marcel(initProperties);

	instance->autorelease();

	return instance;
}

Marcel::Marcel(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Marcel_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Marcel::~Marcel()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
