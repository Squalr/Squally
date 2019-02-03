////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Finch.h"

#include "Resources/EntityResources.h"

const std::string Finch::MapKeyFinch = "finch";

Finch* Finch::deserialize(cocos2d::ValueMap* initProperties)
{
	Finch* instance = new Finch(initProperties);

	instance->autorelease();

	return instance;
}

Finch::Finch(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_SeaSharpCaverns_Finch_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Finch_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Finch::~Finch()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
