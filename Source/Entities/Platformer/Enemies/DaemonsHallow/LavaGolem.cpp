////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "LavaGolem.h"

#include "Resources/EntityResources.h"

const std::string LavaGolem::MapKeyLavaGolem = "lava-golem";

LavaGolem* LavaGolem::deserialize(cocos2d::ValueMap* initProperties)
{
	LavaGolem* instance = new LavaGolem(initProperties);

	instance->autorelease();

	return instance;
}

LavaGolem::LavaGolem(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_LavaGolem_Animations,
	EntityResources::Enemies_DaemonsHallow_LavaGolem_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(980.0f, 1200.0f),
	0.17f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

LavaGolem::~LavaGolem()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
