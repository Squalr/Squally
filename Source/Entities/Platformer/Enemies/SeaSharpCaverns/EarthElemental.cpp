////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "EarthElemental.h"

#include "Resources/EntityResources.h"

const std::string EarthElemental::MapKeyEarthElemental = "earth-elemental";

EarthElemental* EarthElemental::deserialize(cocos2d::ValueMap* initProperties)
{
	EarthElemental* instance = new EarthElemental(initProperties);

	instance->autorelease();

	return instance;
}

EarthElemental::EarthElemental(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_EarthElemental_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(820.0f, 1480.0f),
	0.20f,
	cocos2d::Vec2(0.0f, -740.0f),
	10,
	10)
{
}

EarthElemental::~EarthElemental()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
