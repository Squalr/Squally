////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "SkeletalWarrior.h"

#include "Resources/EntityResources.h"

const std::string SkeletalWarrior::MapKeySkeletalWarrior = "skeletal-warrior";

SkeletalWarrior* SkeletalWarrior::deserialize(cocos2d::ValueMap* initProperties)
{
	SkeletalWarrior* instance = new SkeletalWarrior(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalWarrior::SkeletalWarrior(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SkeletalWarrior_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(128.0f, 216.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

SkeletalWarrior::~SkeletalWarrior()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
