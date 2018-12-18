////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Ares.h"

#include "Resources/EntityResources.h"

const std::string Ares::MapKeyAres = "ares";

Ares* Ares::deserialize(cocos2d::ValueMap* initProperties)
{
	Ares* instance = new Ares(initProperties);

	instance->autorelease();

	return instance;
}

Ares::Ares(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Ares_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Ares::~Ares()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
