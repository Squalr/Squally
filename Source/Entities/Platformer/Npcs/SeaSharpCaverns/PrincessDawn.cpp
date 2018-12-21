////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "PrincessDawn.h"

#include "Resources/EntityResources.h"

const std::string PrincessDawn::MapKeyPrincessDawn = "princess-dawn";

PrincessDawn* PrincessDawn::deserialize(cocos2d::ValueMap* initProperties)
{
	PrincessDawn* instance = new PrincessDawn(initProperties);

	instance->autorelease();

	return instance;
}

PrincessDawn::PrincessDawn(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_SeaSharpCaverns_PrincessDawn_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

PrincessDawn::~PrincessDawn()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
