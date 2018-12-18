////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Sarude.h"

#include "Resources/EntityResources.h"

const std::string Sarude::MapKeySarude = "sarude";

Sarude* Sarude::deserialize(cocos2d::ValueMap* initProperties)
{
	Sarude* instance = new Sarude(initProperties);

	instance->autorelease();

	return instance;
}

Sarude::Sarude(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Sarude_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Sarude::~Sarude()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
