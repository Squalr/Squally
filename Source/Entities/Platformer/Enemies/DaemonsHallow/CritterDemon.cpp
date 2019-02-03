////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "CritterDemon.h"

#include "Resources/EntityResources.h"

const std::string CritterDemon::MapKeyCritterDemon = "critter-demon";

CritterDemon* CritterDemon::deserialize(cocos2d::ValueMap* initProperties)
{
	CritterDemon* instance = new CritterDemon(initProperties);

	instance->autorelease();

	return instance;
}

CritterDemon::CritterDemon(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_CritterDemon_Animations,
	EntityResources::Enemies_DaemonsHallow_CritterDemon_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(188.0f, 160.0f),
	0.7f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

CritterDemon::~CritterDemon()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
