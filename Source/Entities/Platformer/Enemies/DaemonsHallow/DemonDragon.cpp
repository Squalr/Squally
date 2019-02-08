////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "DemonDragon.h"

#include "Resources/EntityResources.h"

const std::string DemonDragon::MapKeyDemonDragon = "demon-dragon";

DemonDragon* DemonDragon::deserialize(cocos2d::ValueMap& initProperties)
{
	DemonDragon* instance = new DemonDragon(initProperties);

	instance->autorelease();

	return instance;
}

DemonDragon::DemonDragon(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonDragon_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonDragon_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(340.0f, 360.0f),
	0.85f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

DemonDragon::~DemonDragon()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
