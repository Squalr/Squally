////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Aspen.h"

#include "Resources/EntityResources.h"

const std::string Aspen::MapKeyAspen = "aspen";

Aspen* Aspen::deserialize(cocos2d::ValueMap* initProperties)
{
	Aspen* instance = new Aspen(initProperties);

	instance->autorelease();

	return instance;
}

Aspen::Aspen(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_LambdaPeaks_Aspen_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Aspen::~Aspen()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
