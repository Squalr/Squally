////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "ToySoldierGoblin.h"

#include "Resources/EntityResources.h"

const std::string ToySoldierGoblin::MapKeyToySoldierGoblin = "toy-soldier-goblin";

ToySoldierGoblin* ToySoldierGoblin::deserialize(cocos2d::ValueMap* initProperties)
{
	ToySoldierGoblin* instance = new ToySoldierGoblin(initProperties);

	instance->autorelease();

	return instance;
}

ToySoldierGoblin::ToySoldierGoblin(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_ToySoldierGoblin_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(112.0f, 288.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

ToySoldierGoblin::~ToySoldierGoblin()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
