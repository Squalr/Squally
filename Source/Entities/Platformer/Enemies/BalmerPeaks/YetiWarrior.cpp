////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "YetiWarrior.h"

#include "Resources/EntityResources.h"

const std::string YetiWarrior::MapKeyYetiWarrior = "yeti-warrior";

YetiWarrior* YetiWarrior::deserialize(cocos2d::ValueMap* initProperties)
{
	YetiWarrior* instance = new YetiWarrior(initProperties);

	instance->autorelease();

	return instance;
}

YetiWarrior::YetiWarrior(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_YetiWarrior_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(380.0f, 572.0f),
	0.4f,
	cocos2d::Vec2(24.0f, 0.0f),
	10,
	10)
{
}

YetiWarrior::~YetiWarrior()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
