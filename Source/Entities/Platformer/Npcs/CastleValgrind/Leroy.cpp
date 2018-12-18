////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Leroy.h"

#include "Resources/EntityResources.h"

const std::string Leroy::MapKeyLeroy = "leroy";

Leroy* Leroy::deserialize(cocos2d::ValueMap* initProperties)
{
	Leroy* instance = new Leroy(initProperties);

	instance->autorelease();

	return instance;
}

Leroy::Leroy(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_CastleValgrind_Leroy_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Leroy::~Leroy()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
