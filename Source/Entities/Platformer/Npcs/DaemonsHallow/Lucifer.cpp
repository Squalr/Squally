////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Lucifer.h"

#include "Resources/EntityResources.h"

const std::string Lucifer::MapKeyLucifer = "lucifer";

Lucifer* Lucifer::deserialize(cocos2d::ValueMap* initProperties)
{
	Lucifer* instance = new Lucifer(initProperties);

	instance->autorelease();

	return instance;
}

Lucifer::Lucifer(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_DaemonsHallow_Lucifer_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Lucifer::~Lucifer()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
