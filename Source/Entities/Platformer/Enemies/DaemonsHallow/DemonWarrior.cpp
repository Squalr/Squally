////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "DemonWarrior.h"

#include "Resources/EntityResources.h"

const std::string DemonWarrior::MapKeyDemonWarrior = "demon-warrior";

DemonWarrior* DemonWarrior::deserialize(cocos2d::ValueMap* initProperties)
{
	DemonWarrior* instance = new DemonWarrior(initProperties);

	instance->autorelease();

	return instance;
}

DemonWarrior::DemonWarrior(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonWarrior_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(320.0f, 372.0f),
	0.7f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

DemonWarrior::~DemonWarrior()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
