////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "PrincessNebea.h"

#include "Resources/EntityResources.h"

const std::string PrincessNebea::MapKeyPrincessNebea = "princess-nebea";

PrincessNebea* PrincessNebea::deserialize(cocos2d::ValueMap* initProperties)
{
	PrincessNebea* instance = new PrincessNebea(initProperties);

	instance->autorelease();

	return instance;
}

PrincessNebea::PrincessNebea(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_LexiconCrypts_PrincessNebea_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

PrincessNebea::~PrincessNebea()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
