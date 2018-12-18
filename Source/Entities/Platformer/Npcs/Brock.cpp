////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Brock.h"

#include "Resources/EntityResources.h"

const std::string Brock::MapKeyBrock = "brock";

Brock* Brock::deserialize(cocos2d::ValueMap* initProperties)
{
	Brock* instance = new Brock(initProperties);

	instance->autorelease();

	return instance;
}

Brock::Brock(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Brock_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Brock::~Brock()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
