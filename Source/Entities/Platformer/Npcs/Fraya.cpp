////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Fraya.h"

#include "Resources/EntityResources.h"

const std::string Fraya::MapKeyFraya = "fraya";

Fraya* Fraya::deserialize(cocos2d::ValueMap* initProperties)
{
	Fraya* instance = new Fraya(initProperties);

	instance->autorelease();

	return instance;
}

Fraya::Fraya(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Fraya_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Fraya::~Fraya()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
