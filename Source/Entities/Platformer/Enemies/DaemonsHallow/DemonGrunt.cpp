////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "DemonGrunt.h"

#include "Resources/EntityResources.h"

const std::string DemonGrunt::MapKeyDemonGrunt = "demon-grunt";

DemonGrunt* DemonGrunt::deserialize(cocos2d::ValueMap* initProperties)
{
	DemonGrunt* instance = new DemonGrunt(initProperties);

	instance->autorelease();

	return instance;
}

DemonGrunt::DemonGrunt(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonGrunt_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(312.0f, 372.0f),
	0.7f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

DemonGrunt::~DemonGrunt()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
