////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Gramps.h"

#include "Resources/EntityResources.h"

const std::string Gramps::MapKeyGramps = "gramps";

Gramps* Gramps::deserialize(cocos2d::ValueMap* initProperties)
{
	Gramps* instance = new Gramps(initProperties);

	instance->autorelease();

	return instance;
}

Gramps::Gramps(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_Gramps_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Gramps::~Gramps()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
