////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "QueenElise.h"

#include "Resources/EntityResources.h"

const std::string QueenElise::MapKeyQueenElise = "queen-elise";

QueenElise* QueenElise::deserialize(cocos2d::ValueMap* initProperties)
{
	QueenElise* instance = new QueenElise(initProperties);

	instance->autorelease();

	return instance;
}

QueenElise::QueenElise(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_VoidStar_QueenElise_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

QueenElise::~QueenElise()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
