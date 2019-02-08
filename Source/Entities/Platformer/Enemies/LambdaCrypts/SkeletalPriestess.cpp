////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "SkeletalPriestess.h"

#include "Resources/EntityResources.h"

const std::string SkeletalPriestess::MapKeySkeletalPriestess = "skeletal-priestess";

SkeletalPriestess* SkeletalPriestess::deserialize(cocos2d::ValueMap& initProperties)
{
	SkeletalPriestess* instance = new SkeletalPriestess(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalPriestess::SkeletalPriestess(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_SkeletalPriestess_Animations,
	EntityResources::Enemies_LambdaCrypts_SkeletalPriestess_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(196.0f, 312.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

SkeletalPriestess::~SkeletalPriestess()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
