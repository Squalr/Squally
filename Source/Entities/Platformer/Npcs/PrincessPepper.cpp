////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "PrincessPepper.h"

#include "Resources/EntityResources.h"

const std::string PrincessPepper::MapKeyPrincessPepper = "princess-pepper";

PrincessPepper* PrincessPepper::deserialize(cocos2d::ValueMap* initProperties)
{
	PrincessPepper* instance = new PrincessPepper(initProperties);

	instance->autorelease();

	return instance;
}

PrincessPepper::PrincessPepper(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_PrincessPepper_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

PrincessPepper::~PrincessPepper()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
