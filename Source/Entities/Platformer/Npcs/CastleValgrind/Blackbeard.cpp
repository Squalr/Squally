////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Blackbeard.h"

#include "Resources/EntityResources.h"

const std::string Blackbeard::MapKeyBlackbeard = "blackbeard";

Blackbeard* Blackbeard::deserialize(cocos2d::ValueMap* initProperties)
{
	Blackbeard* instance = new Blackbeard(initProperties);

	instance->autorelease();

	return instance;
}

Blackbeard::Blackbeard(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_CastleValgrind_Blackbeard_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Blackbeard::~Blackbeard()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
