////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Garrick.h"

#include "Resources/EntityResources.h"

const std::string Garrick::MapKeyGarrick = "garrick";

Garrick* Garrick::deserialize(cocos2d::ValueMap* initProperties)
{
	Garrick* instance = new Garrick(initProperties);

	instance->autorelease();

	return instance;
}

Garrick::Garrick(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_LambdaCrypts_Garrick_Animations,
	EntityResources::Npcs_LambdaCrypts_Garrick_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Garrick::~Garrick()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
