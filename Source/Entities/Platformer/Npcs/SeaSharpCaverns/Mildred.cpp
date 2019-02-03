////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Mildred.h"

#include "Resources/EntityResources.h"

const std::string Mildred::MapKeyMildred = "mildred";

Mildred* Mildred::deserialize(cocos2d::ValueMap* initProperties)
{
	Mildred* instance = new Mildred(initProperties);

	instance->autorelease();

	return instance;
}

Mildred::Mildred(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_SeaSharpCaverns_Mildred_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Mildred_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Mildred::~Mildred()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
