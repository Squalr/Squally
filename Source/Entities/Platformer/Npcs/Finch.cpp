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
	EntityResources::Npcs_Finch_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
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
