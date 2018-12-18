////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "SkeletalNecromancer.h"

#include "Resources/EntityResources.h"

const std::string SkeletalNecromancer::MapKeySkeletalNecromancer = "skeletal-necromancer";

SkeletalNecromancer* SkeletalNecromancer::deserialize(cocos2d::ValueMap* initProperties)
{
	SkeletalNecromancer* instance = new SkeletalNecromancer(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalNecromancer::SkeletalNecromancer(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SkeletalNecromancer_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(128.0f, 228.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

SkeletalNecromancer::~SkeletalNecromancer()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
