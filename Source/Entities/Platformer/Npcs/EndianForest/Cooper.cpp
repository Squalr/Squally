////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Cooper.h"

#include "Resources/EntityResources.h"

const std::string Cooper::MapKeyCooper = "cooper";

Cooper* Cooper::deserialize(cocos2d::ValueMap* initProperties)
{
	Cooper* instance = new Cooper(initProperties);

	instance->autorelease();

	return instance;
}

Cooper::Cooper(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_Cooper_Animations,
	EntityResources::Npcs_EndianForest_Cooper_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Cooper::~Cooper()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
