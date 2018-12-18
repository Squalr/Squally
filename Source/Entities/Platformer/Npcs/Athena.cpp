////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Athena.h"

#include "Resources/EntityResources.h"

const std::string Athena::MapKeyAthena = "athena";

Athena* Athena::deserialize(cocos2d::ValueMap* initProperties)
{
	Athena* instance = new Athena(initProperties);

	instance->autorelease();

	return instance;
}

Athena::Athena(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Athena_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Athena::~Athena()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
