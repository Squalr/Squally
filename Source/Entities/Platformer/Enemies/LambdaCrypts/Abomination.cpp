////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Abomination.h"

#include "Resources/EntityResources.h"

const std::string Abomination::MapKeyAbomination = "abomination";

Abomination* Abomination::deserialize(cocos2d::ValueMap& initProperties)
{
	Abomination* instance = new Abomination(initProperties);

	instance->autorelease();

	return instance;
}

Abomination::Abomination(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_Abomination_Animations,
	EntityResources::Enemies_LambdaCrypts_Abomination_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(296.0f, 356.0f),
	0.6f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Abomination::~Abomination()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
