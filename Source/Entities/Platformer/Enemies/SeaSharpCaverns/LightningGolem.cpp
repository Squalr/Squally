////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "LightningGolem.h"

#include "Resources/EntityResources.h"

const std::string LightningGolem::MapKeyLightningGolem = "lightning-golem";

LightningGolem* LightningGolem::deserialize(cocos2d::ValueMap* initProperties)
{
	LightningGolem* instance = new LightningGolem(initProperties);

	instance->autorelease();

	return instance;
}

LightningGolem::LightningGolem(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_LightningGolem_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(768.0f, 840.0f),
	0.30f,
	cocos2d::Vec2(0.0f, -420.0f),
	10,
	10)
{
}

LightningGolem::~LightningGolem()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
