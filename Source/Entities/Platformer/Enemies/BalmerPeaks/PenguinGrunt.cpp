////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "PenguinGrunt.h"

#include "Resources/EntityResources.h"

const std::string PenguinGrunt::MapKeyPenguinGrunt = "penguin-grunt";

PenguinGrunt* PenguinGrunt::deserialize(cocos2d::ValueMap* initProperties)
{
	PenguinGrunt* instance = new PenguinGrunt(initProperties);

	instance->autorelease();

	return instance;
}

PenguinGrunt::PenguinGrunt(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_PenguinGrunt_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(212.0f, 296.0f),
	0.7f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

PenguinGrunt::~PenguinGrunt()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
