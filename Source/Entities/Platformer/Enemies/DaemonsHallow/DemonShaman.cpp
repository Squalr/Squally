////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "DemonShaman.h"

#include "Resources/EntityResources.h"

const std::string DemonShaman::MapKeyDemonShaman = "demon-shaman";

DemonShaman* DemonShaman::deserialize(cocos2d::ValueMap* initProperties)
{
	DemonShaman* instance = new DemonShaman(initProperties);

	instance->autorelease();

	return instance;
}

DemonShaman::DemonShaman(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonShaman_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(212.0f, 280.0f),
	0.65f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

DemonShaman::~DemonShaman()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
