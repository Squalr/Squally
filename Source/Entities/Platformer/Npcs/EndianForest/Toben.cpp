////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Toben.h"

#include "Resources/EntityResources.h"

const std::string Toben::MapKeyToben = "toben";

Toben* Toben::deserialize(cocos2d::ValueMap& initProperties)
{
	Toben* instance = new Toben(initProperties);

	instance->autorelease();

	return instance;
}

Toben::Toben(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_Toben_Animations,
	EntityResources::Npcs_EndianForest_Toben_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Toben::~Toben()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
