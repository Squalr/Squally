////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Necron.h"

#include "Resources/EntityResources.h"

const std::string Necron::MapKeyNecron = "necron";

Necron* Necron::deserialize(cocos2d::ValueMap* initProperties)
{
	Necron* instance = new Necron(initProperties);

	instance->autorelease();

	return instance;
}

Necron::Necron(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Necron_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Necron::~Necron()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
