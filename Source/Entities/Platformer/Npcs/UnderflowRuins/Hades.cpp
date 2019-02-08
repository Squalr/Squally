////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Hades.h"

#include "Resources/EntityResources.h"

const std::string Hades::MapKeyHades = "hades";

Hades* Hades::deserialize(cocos2d::ValueMap& initProperties)
{
	Hades* instance = new Hades(initProperties);

	instance->autorelease();

	return instance;
}

Hades::Hades(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_UnderflowRuins_Hades_Animations,
	EntityResources::Npcs_UnderflowRuins_Hades_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Hades::~Hades()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
