////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Dudly.h"

#include "Resources/EntityResources.h"

const std::string Dudly::MapKeyDudly = "dudly";

Dudly* Dudly::deserialize(cocos2d::ValueMap* initProperties)
{
	Dudly* instance = new Dudly(initProperties);

	instance->autorelease();

	return instance;
}

Dudly::Dudly(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Dudly_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Dudly::~Dudly()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
