////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "GoblinElf.h"

#include "Resources/EntityResources.h"

const std::string GoblinElf::MapKeyGoblinElf = "goblin-elf";

GoblinElf* GoblinElf::deserialize(cocos2d::ValueMap& initProperties)
{
	GoblinElf* instance = new GoblinElf(initProperties);

	instance->autorelease();

	return instance;
}

GoblinElf::GoblinElf(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_GoblinElf_Animations,
	EntityResources::Enemies_BalmerPeaks_GoblinElf_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(140.0f, 296.0f),
	0.6f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

GoblinElf::~GoblinElf()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
