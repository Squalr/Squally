////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Zana.h"

#include "Resources/EntityResources.h"

const std::string Zana::MapKeyZana = "zana";

Zana* Zana::deserialize(cocos2d::ValueMap* initProperties)
{
	Zana* instance = new Zana(initProperties);

	instance->autorelease();

	return instance;
}

Zana::Zana(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_LexiconCrypts_Zana_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Zana::~Zana()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
