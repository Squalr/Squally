////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Geryon.h"

#include "Resources/EntityResources.h"

const std::string Geryon::MapKeyGeryon = "geryon";

Geryon* Geryon::deserialize(cocos2d::ValueMap* initProperties)
{
	Geryon* instance = new Geryon(initProperties);

	instance->autorelease();

	return instance;
}

Geryon::Geryon(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Geryon_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Geryon::~Geryon()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
