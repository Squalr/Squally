////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "DemonSwordsman.h"

#include "Resources/EntityResources.h"

const std::string DemonSwordsman::MapKeyDemonSwordsman = "demon-swordsman";

DemonSwordsman* DemonSwordsman::deserialize(cocos2d::ValueMap& initProperties)
{
	DemonSwordsman* instance = new DemonSwordsman(initProperties);

	instance->autorelease();

	return instance;
}

DemonSwordsman::DemonSwordsman(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonSwordsman_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonSwordsman_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(212.0f, 268.0f),
	0.65f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

DemonSwordsman::~DemonSwordsman()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
