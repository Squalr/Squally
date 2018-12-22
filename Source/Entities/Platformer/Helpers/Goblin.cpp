////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Goblin.h"

#include "Resources/EntityResources.h"

const std::string Goblin::MapKeyGoblin = "goblin";

Goblin* Goblin::deserialize(cocos2d::ValueMap* initProperties)
{
	Goblin* instance = new Goblin(initProperties);

	instance->autorelease();

	return instance;
}

Goblin::Goblin(cocos2d::ValueMap* initProperties) : PlatformerEntity(initProperties,
	EntityResources::Helpers_Goblin_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(224.0f, 440.0f),
	0.3f,
	cocos2d::Vec2(0.0f, -220.0f))
{
}

Goblin::~Goblin()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
