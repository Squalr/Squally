////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Zeus.h"

#include "Resources/EntityResources.h"

const std::string Zeus::MapKeyZeus = "zeus";

Zeus* Zeus::deserialize(cocos2d::ValueMap& initProperties)
{
	Zeus* instance = new Zeus(initProperties);

	instance->autorelease();

	return instance;
}

Zeus::Zeus(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_UnderflowRuins_Zeus_Animations,
	EntityResources::Npcs_UnderflowRuins_Zeus_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Zeus::~Zeus()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
