////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Cleopatra.h"

#include "Resources/EntityResources.h"

const std::string Cleopatra::MapKeyCleopatra = "cleopatra";

Cleopatra* Cleopatra::deserialize(cocos2d::ValueMap* initProperties)
{
	Cleopatra* instance = new Cleopatra(initProperties);

	instance->autorelease();

	return instance;
}

Cleopatra::Cleopatra(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Cleopatra_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Cleopatra::~Cleopatra()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
