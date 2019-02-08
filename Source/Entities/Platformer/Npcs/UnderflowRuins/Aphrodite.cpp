////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Aphrodite.h"

#include "Resources/EntityResources.h"

const std::string Aphrodite::MapKeyAphrodite = "aphrodite";

Aphrodite* Aphrodite::deserialize(cocos2d::ValueMap& initProperties)
{
	Aphrodite* instance = new Aphrodite(initProperties);

	instance->autorelease();

	return instance;
}

Aphrodite::Aphrodite(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_UnderflowRuins_Aphrodite_Animations,
	EntityResources::Npcs_UnderflowRuins_Aphrodite_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Aphrodite::~Aphrodite()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
