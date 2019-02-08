////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Celeste.h"

#include "Resources/EntityResources.h"

const std::string Celeste::MapKeyCeleste = "celeste";

Celeste* Celeste::deserialize(cocos2d::ValueMap& initProperties)
{
	Celeste* instance = new Celeste(initProperties);

	instance->autorelease();

	return instance;
}

Celeste::Celeste(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_DaemonsHallow_Celeste_Animations,
	EntityResources::Npcs_DaemonsHallow_Celeste_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Celeste::~Celeste()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
