////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "PrincessMittens.h"

#include "Resources/EntityResources.h"

const std::string PrincessMittens::MapKeyPrincessMittens = "princess-mittens";

PrincessMittens* PrincessMittens::deserialize(cocos2d::ValueMap& initProperties)
{
	PrincessMittens* instance = new PrincessMittens(initProperties);

	instance->autorelease();

	return instance;
}

PrincessMittens::PrincessMittens(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_DaemonsHallow_PrincessMittens_Animations,
	EntityResources::Npcs_DaemonsHallow_PrincessMittens_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

PrincessMittens::~PrincessMittens()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
