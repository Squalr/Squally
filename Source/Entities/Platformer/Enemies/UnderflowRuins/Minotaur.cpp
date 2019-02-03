////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Minotaur.h"

#include "Resources/EntityResources.h"

const std::string Minotaur::MapKeyMinotaur = "minotaur";

Minotaur* Minotaur::deserialize(cocos2d::ValueMap* initProperties)
{
	Minotaur* instance = new Minotaur(initProperties);

	instance->autorelease();

	return instance;
}

Minotaur::Minotaur(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_Minotaur_Animations,
	EntityResources::Enemies_UnderflowRuins_Minotaur_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(278.0f, 288.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Minotaur::~Minotaur()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
