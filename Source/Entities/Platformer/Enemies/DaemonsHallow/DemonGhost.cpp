////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "DemonGhost.h"

#include "Resources/EntityResources.h"

const std::string DemonGhost::MapKeyDemonGhost = "demon-ghost";

DemonGhost* DemonGhost::deserialize(cocos2d::ValueMap* initProperties)
{
	DemonGhost* instance = new DemonGhost(initProperties);

	instance->autorelease();

	return instance;
}

DemonGhost::DemonGhost(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonGhost_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 320.0f),
	0.7f,
	cocos2d::Vec2(0.0f, 40.0f),
	10,
	10)
{
}

DemonGhost::~DemonGhost()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
