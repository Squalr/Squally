////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Ragnis.h"

#include "Resources/EntityResources.h"

const std::string Ragnis::MapKeyRagnis = "ragnis";

Ragnis* Ragnis::deserialize(cocos2d::ValueMap* initProperties)
{
	Ragnis* instance = new Ragnis(initProperties);

	instance->autorelease();

	return instance;
}

Ragnis::Ragnis(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Ragnis_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Ragnis::~Ragnis()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
