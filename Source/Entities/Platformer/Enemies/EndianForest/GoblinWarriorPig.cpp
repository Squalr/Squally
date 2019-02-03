////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "GoblinWarriorPig.h"

#include "Resources/EntityResources.h"

const std::string GoblinWarriorPig::MapKeyGoblinWarriorPig = "goblin-warrior-pig";

GoblinWarriorPig* GoblinWarriorPig::deserialize(cocos2d::ValueMap* initProperties)
{
	GoblinWarriorPig* instance = new GoblinWarriorPig(initProperties);

	instance->autorelease();

	return instance;
}

GoblinWarriorPig::GoblinWarriorPig(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_GoblinWarriorPig_Animations,
	EntityResources::Enemies_EndianForest_GoblinWarriorPig_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(128.0f, 296.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

GoblinWarriorPig::~GoblinWarriorPig()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
