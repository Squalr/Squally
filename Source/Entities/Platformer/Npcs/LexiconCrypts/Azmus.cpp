////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Azmus.h"

#include "Resources/EntityResources.h"

const std::string Azmus::MapKeyAzmus = "azmus";

Azmus* Azmus::deserialize(cocos2d::ValueMap* initProperties)
{
	Azmus* instance = new Azmus(initProperties);

	instance->autorelease();

	return instance;
}

Azmus::Azmus(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_LexiconCrypts_Azmus_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Azmus::~Azmus()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
