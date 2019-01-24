////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "SkeletalCleaver.h"

#include "Resources/EntityResources.h"

const std::string SkeletalCleaver::MapKeySkeletalCleaver = "skeletal-cleaver";

SkeletalCleaver* SkeletalCleaver::deserialize(cocos2d::ValueMap* initProperties)
{
	SkeletalCleaver* instance = new SkeletalCleaver(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalCleaver::SkeletalCleaver(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LexiconCrypts_SkeletalCleaver_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(128.0f, 312.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 16.0f),
	10,
	10)
{
}

SkeletalCleaver::~SkeletalCleaver()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
