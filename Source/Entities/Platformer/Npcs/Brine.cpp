////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Brine.h"

#include "Resources/EntityResources.h"

const std::string Brine::MapKeyBrine = "brine";

Brine* Brine::deserialize(cocos2d::ValueMap* initProperties)
{
	Brine* instance = new Brine(initProperties);

	instance->autorelease();

	return instance;
}

Brine::Brine(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Brine_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Brine::~Brine()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
