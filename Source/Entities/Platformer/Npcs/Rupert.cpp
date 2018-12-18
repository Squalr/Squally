////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Rupert.h"

#include "Resources/EntityResources.h"

const std::string Rupert::MapKeyRupert = "rupert";

Rupert* Rupert::deserialize(cocos2d::ValueMap* initProperties)
{
	Rupert* instance = new Rupert(initProperties);

	instance->autorelease();

	return instance;
}

Rupert::Rupert(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Rupert_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
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
