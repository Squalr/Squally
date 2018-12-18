////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "OrcGrunt.h"

#include "Resources/EntityResources.h"

const std::string OrcGrunt::MapKeyOrcGrunt = "orc-grunt";

OrcGrunt* OrcGrunt::deserialize(cocos2d::ValueMap* initProperties)
{
	OrcGrunt* instance = new OrcGrunt(initProperties);

	instance->autorelease();

	return instance;
}

OrcGrunt::OrcGrunt(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_OrcGrunt_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 218.0f),
	1.0f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

OrcGrunt::~OrcGrunt()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
