////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "GoblinGruntBoar.h"

#include "Resources/EntityResources.h"

const std::string GoblinGruntBoar::MapKeyGoblinGruntBoar = "goblin-grunt-boar";

GoblinGruntBoar* GoblinGruntBoar::deserialize(cocos2d::ValueMap* initProperties)
{
	GoblinGruntBoar* instance = new GoblinGruntBoar(initProperties);

	instance->autorelease();

	return instance;
}

GoblinGruntBoar::GoblinGruntBoar(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_GoblinGruntBoar_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(128.0f, 296.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

GoblinGruntBoar::~GoblinGruntBoar()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
