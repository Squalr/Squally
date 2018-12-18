////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "PrincessMittens.h"

#include "Resources/EntityResources.h"

const std::string PrincessMittens::MapKeyPrincessMittens = "princess-mittens";

PrincessMittens* PrincessMittens::deserialize(cocos2d::ValueMap* initProperties)
{
	PrincessMittens* instance = new PrincessMittens(initProperties);

	instance->autorelease();

	return instance;
}

PrincessMittens::PrincessMittens(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_PrincessMittens_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
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
