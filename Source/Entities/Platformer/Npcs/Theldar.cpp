////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Theldar.h"

#include "Resources/EntityResources.h"

const std::string Theldar::MapKeyTheldar = "theldar";

Theldar* Theldar::deserialize(cocos2d::ValueMap* initProperties)
{
	Theldar* instance = new Theldar(initProperties);

	instance->autorelease();

	return instance;
}

Theldar::Theldar(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Theldar_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Theldar::~Theldar()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
