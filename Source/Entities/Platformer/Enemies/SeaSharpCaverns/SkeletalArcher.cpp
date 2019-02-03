////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "SkeletalArcher.h"

#include "Resources/EntityResources.h"

const std::string SkeletalArcher::MapKeySkeletalArcher = "skeletal-archer";

SkeletalArcher* SkeletalArcher::deserialize(cocos2d::ValueMap* initProperties)
{
	SkeletalArcher* instance = new SkeletalArcher(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalArcher::SkeletalArcher(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalArcher_Animations,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalArcher_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(128.0f, 216.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

SkeletalArcher::~SkeletalArcher()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
