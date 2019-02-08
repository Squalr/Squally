////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Ghost.h"

#include "Resources/EntityResources.h"

const std::string Ghost::MapKeyGhost = "ghost";

Ghost* Ghost::deserialize(cocos2d::ValueMap& initProperties)
{
	Ghost* instance = new Ghost(initProperties);

	instance->autorelease();

	return instance;
}

Ghost::Ghost(cocos2d::ValueMap& initProperties) : PlatformerEntity(initProperties,
	EntityResources::Helpers_Ghost_Animations,
	EntityResources::Helpers_Ghost_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(224.0f, 440.0f),
	0.3f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Ghost::~Ghost()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
