////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Rusty.h"

#include "Resources/EntityResources.h"

const std::string Rusty::MapKeyRusty = "rusty";

Rusty* Rusty::deserialize(cocos2d::ValueMap& initProperties)
{
	Rusty* instance = new Rusty(initProperties);

	instance->autorelease();

	return instance;
}

Rusty::Rusty(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_Rusty_Animations,
	EntityResources::Npcs_EndianForest_Rusty_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Rusty::~Rusty()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
