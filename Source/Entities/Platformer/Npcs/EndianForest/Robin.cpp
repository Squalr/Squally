////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Robin.h"

#include "Resources/EntityResources.h"

const std::string Robin::MapKeyRobin = "robin";

Robin* Robin::deserialize(cocos2d::ValueMap* initProperties)
{
	Robin* instance = new Robin(initProperties);

	instance->autorelease();

	return instance;
}

Robin::Robin(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_Robin_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Robin::~Robin()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
