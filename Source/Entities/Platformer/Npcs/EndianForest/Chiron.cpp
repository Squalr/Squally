////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Chiron.h"

#include "Resources/EntityResources.h"

const std::string Chiron::MapKeyChiron = "chiron";

Chiron* Chiron::deserialize(cocos2d::ValueMap* initProperties)
{
	Chiron* instance = new Chiron(initProperties);

	instance->autorelease();

	return instance;
}

Chiron::Chiron(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_Chiron_Animations,
	EntityResources::Npcs_EndianForest_Chiron_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(160.0f, 224.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Chiron::~Chiron()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
