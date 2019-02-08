////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "MummyWarrior.h"

#include "Resources/EntityResources.h"

const std::string MummyWarrior::MapKeyMummyWarrior = "mummy-warrior";

MummyWarrior* MummyWarrior::deserialize(cocos2d::ValueMap& initProperties)
{
	MummyWarrior* instance = new MummyWarrior(initProperties);

	instance->autorelease();

	return instance;
}

MummyWarrior::MummyWarrior(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_MummyWarrior_Animations,
	EntityResources::Enemies_UnderflowRuins_MummyWarrior_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(128.0f, 256.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

MummyWarrior::~MummyWarrior()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
