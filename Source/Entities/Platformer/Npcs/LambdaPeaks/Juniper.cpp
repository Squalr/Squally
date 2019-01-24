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
	EntityResources::Npcs_LambdaPeaks_Juniper_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
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
