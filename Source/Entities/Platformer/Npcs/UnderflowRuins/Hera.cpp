////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Hera.h"

#include "Resources/EntityResources.h"

const std::string Hera::MapKeyHera = "hera";

Hera* Hera::deserialize(cocos2d::ValueMap* initProperties)
{
	Hera* instance = new Hera(initProperties);

	instance->autorelease();

	return instance;
}

Hera::Hera(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_UnderflowRuins_Hera_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Hera::~Hera()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
