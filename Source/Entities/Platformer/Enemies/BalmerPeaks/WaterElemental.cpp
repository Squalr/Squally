////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "WaterElemental.h"

#include "Resources/EntityResources.h"

const std::string WaterElemental::MapKeyWaterElemental = "water-elemental";

WaterElemental* WaterElemental::deserialize(cocos2d::ValueMap* initProperties)
{
	WaterElemental* instance = new WaterElemental(initProperties);

	instance->autorelease();

	return instance;
}

WaterElemental::WaterElemental(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_WaterElemental_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(820.0f, 1480.0f),
	0.20f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

WaterElemental::~WaterElemental()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
