////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Juniper.h"

#include "Resources/EntityResources.h"

const std::string Juniper::MapKeyJuniper = "juniper";

Juniper* Juniper::deserialize(cocos2d::ValueMap* initProperties)
{
	Juniper* instance = new Juniper(initProperties);

	instance->autorelease();

	return instance;
}

Juniper::Juniper(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Juniper_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Juniper::~Juniper()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
