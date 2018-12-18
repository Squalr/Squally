////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Irmik.h"

#include "Resources/EntityResources.h"

const std::string Irmik::MapKeyIrmik = "irmik";

Irmik* Irmik::deserialize(cocos2d::ValueMap* initProperties)
{
	Irmik* instance = new Irmik(initProperties);

	instance->autorelease();

	return instance;
}

Irmik::Irmik(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Irmik_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Irmik::~Irmik()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
