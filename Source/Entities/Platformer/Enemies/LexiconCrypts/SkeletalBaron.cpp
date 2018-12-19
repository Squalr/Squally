////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "SkeletalBaron.h"

#include "Resources/EntityResources.h"

const std::string SkeletalBaron::MapKeySkeletalBaron = "skeletal-baron";

SkeletalBaron* SkeletalBaron::deserialize(cocos2d::ValueMap* initProperties)
{
	SkeletalBaron* instance = new SkeletalBaron(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalBaron::SkeletalBaron(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LexiconCrypts_SkeletalBaron_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(112.0f, 368.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

SkeletalBaron::~SkeletalBaron()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
