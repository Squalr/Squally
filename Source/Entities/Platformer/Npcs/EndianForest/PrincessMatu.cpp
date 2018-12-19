////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "PrincessMatu.h"

#include "Resources/EntityResources.h"

const std::string PrincessMatu::MapKeyPrincessMatu = "princess-matu";

PrincessMatu* PrincessMatu::deserialize(cocos2d::ValueMap* initProperties)
{
	PrincessMatu* instance = new PrincessMatu(initProperties);

	instance->autorelease();

	return instance;
}

PrincessMatu::PrincessMatu(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_PrincessMatu_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	1.0f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

PrincessMatu::~PrincessMatu()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
