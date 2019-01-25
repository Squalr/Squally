////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "ReanimatedPig.h"

#include "Resources/EntityResources.h"

const std::string ReanimatedPig::MapKeyReanimatedPig = "reanimated-pig";

ReanimatedPig* ReanimatedPig::deserialize(cocos2d::ValueMap* initProperties)
{
	ReanimatedPig* instance = new ReanimatedPig(initProperties);

	instance->autorelease();

	return instance;
}

ReanimatedPig::ReanimatedPig(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_ReanimatedPig_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 240.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

ReanimatedPig::~ReanimatedPig()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
