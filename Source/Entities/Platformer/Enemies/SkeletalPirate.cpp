////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "SkeletalPirate.h"

#include "Resources/EntityResources.h"

const std::string SkeletalPirate::MapKeySkeletalPirate = "skeletal-pirate";

SkeletalPirate* SkeletalPirate::deserialize(cocos2d::ValueMap* initProperties)
{
	SkeletalPirate* instance = new SkeletalPirate(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalPirate::SkeletalPirate(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SkeletalPirate_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(284.0f, 256.0f),
	1.0f,
	cocos2d::Vec2(0.0f, -112.0f))
{
}

SkeletalPirate::~SkeletalPirate()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
