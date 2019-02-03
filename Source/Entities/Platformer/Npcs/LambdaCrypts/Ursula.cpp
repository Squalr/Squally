////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Ursula.h"

#include "Resources/EntityResources.h"

const std::string Ursula::MapKeyUrsula = "ursula";

Ursula* Ursula::deserialize(cocos2d::ValueMap* initProperties)
{
	Ursula* instance = new Ursula(initProperties);

	instance->autorelease();

	return instance;
}

Ursula::Ursula(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_LambdaCrypts_Ursula_Animations,
	EntityResources::Npcs_LambdaCrypts_Ursula_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Ursula::~Ursula()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
