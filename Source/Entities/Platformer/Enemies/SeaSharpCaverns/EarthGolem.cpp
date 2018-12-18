////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "EarthGolem.h"

#include "Resources/EntityResources.h"

const std::string EarthGolem::MapKeyEarthGolem = "earth-golem";

EarthGolem* EarthGolem::deserialize(cocos2d::ValueMap* initProperties)
{
	EarthGolem* instance = new EarthGolem(initProperties);

	instance->autorelease();

	return instance;
}

EarthGolem::EarthGolem(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_EarthGolem_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 224.0f),
	1.0f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

EarthGolem::~EarthGolem()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
