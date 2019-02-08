////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Raven.h"

#include "Resources/EntityResources.h"

const std::string Raven::MapKeyRaven = "raven";

Raven* Raven::deserialize(cocos2d::ValueMap& initProperties)
{
	Raven* instance = new Raven(initProperties);

	instance->autorelease();

	return instance;
}

Raven::Raven(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_CastleValgrind_Raven_Animations,
	EntityResources::Npcs_CastleValgrind_Raven_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Raven::~Raven()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
