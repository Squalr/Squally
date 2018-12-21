////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Ash.h"

#include "Resources/EntityResources.h"

const std::string Ash::MapKeyAsh = "ash";

Ash* Ash::deserialize(cocos2d::ValueMap* initProperties)
{
	Ash* instance = new Ash(initProperties);

	instance->autorelease();

	return instance;
}

Ash::Ash(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_DaemonsHallow_Ash_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Ash::~Ash()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
