////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Thion.h"

#include "Resources/EntityResources.h"

const std::string Thion::MapKeyThion = "thion";

Thion* Thion::deserialize(cocos2d::ValueMap* initProperties)
{
	Thion* instance = new Thion(initProperties);

	instance->autorelease();

	return instance;
}

Thion::Thion(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_LambdaCrypts_Thion_Animations,
	EntityResources::Npcs_LambdaCrypts_Thion_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Thion::~Thion()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
