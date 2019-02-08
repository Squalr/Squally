////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Igneus.h"

#include "Resources/EntityResources.h"

const std::string Igneus::MapKeyIgneus = "igneus";

Igneus* Igneus::deserialize(cocos2d::ValueMap& initProperties)
{
	Igneus* instance = new Igneus(initProperties);

	instance->autorelease();

	return instance;
}

Igneus::Igneus(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_DaemonsHallow_Igneus_Animations,
	EntityResources::Npcs_DaemonsHallow_Igneus_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Igneus::~Igneus()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
