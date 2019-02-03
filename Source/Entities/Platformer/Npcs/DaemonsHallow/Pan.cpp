////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Pan.h"

#include "Resources/EntityResources.h"

const std::string Pan::MapKeyPan = "pan";

Pan* Pan::deserialize(cocos2d::ValueMap* initProperties)
{
	Pan* instance = new Pan(initProperties);

	instance->autorelease();

	return instance;
}

Pan::Pan(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_DaemonsHallow_Pan_Animations,
	EntityResources::Npcs_DaemonsHallow_Pan_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Pan::~Pan()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
