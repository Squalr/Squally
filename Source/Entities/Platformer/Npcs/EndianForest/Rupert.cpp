////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Rupert.h"

#include "Resources/EntityResources.h"

const std::string Rupert::MapKeyRupert = "rupert";

Rupert* Rupert::deserialize(cocos2d::ValueMap& initProperties)
{
	Rupert* instance = new Rupert(initProperties);

	instance->autorelease();

	return instance;
}

Rupert::Rupert(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_Rupert_Animations,
	EntityResources::Npcs_EndianForest_Rupert_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Rupert::~Rupert()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
