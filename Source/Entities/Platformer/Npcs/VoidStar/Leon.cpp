////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Leon.h"

#include "Resources/EntityResources.h"

const std::string Leon::MapKeyLeon = "leon";

Leon* Leon::deserialize(cocos2d::ValueMap& initProperties)
{
	Leon* instance = new Leon(initProperties);

	instance->autorelease();

	return instance;
}

Leon::Leon(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_VoidStar_Leon_Animations,
	EntityResources::Npcs_VoidStar_Leon_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Leon::~Leon()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
