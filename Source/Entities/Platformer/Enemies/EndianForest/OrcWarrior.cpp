////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "OrcWarrior.h"

#include "Resources/EntityResources.h"

const std::string OrcWarrior::MapKeyOrcWarrior = "orc-warrior";

OrcWarrior* OrcWarrior::deserialize(cocos2d::ValueMap* initProperties)
{
	OrcWarrior* instance = new OrcWarrior(initProperties);

	instance->autorelease();

	return instance;
}

OrcWarrior::OrcWarrior(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_OrcWarrior_Animations,
	EntityResources::Enemies_EndianForest_OrcWarrior_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 228.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

OrcWarrior::~OrcWarrior()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
