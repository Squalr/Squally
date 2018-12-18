////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "PrincessOpal.h"

#include "Resources/EntityResources.h"

const std::string PrincessOpal::MapKeyPrincessOpal = "princess-opal";

PrincessOpal* PrincessOpal::deserialize(cocos2d::ValueMap* initProperties)
{
	PrincessOpal* instance = new PrincessOpal(initProperties);

	instance->autorelease();

	return instance;
}

PrincessOpal::PrincessOpal(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_CastleValgrind_PrincessOpal_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

PrincessOpal::~PrincessOpal()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
