////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Scaldor.h"

#include "Resources/EntityResources.h"

const std::string Scaldor::MapKeyScaldor = "scaldor";

Scaldor* Scaldor::deserialize(cocos2d::ValueMap* initProperties)
{
	Scaldor* instance = new Scaldor(initProperties);

	instance->autorelease();

	return instance;
}

Scaldor::Scaldor(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_DaemonsHallow_Scaldor_Animations,
	EntityResources::Npcs_DaemonsHallow_Scaldor_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Scaldor::~Scaldor()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
