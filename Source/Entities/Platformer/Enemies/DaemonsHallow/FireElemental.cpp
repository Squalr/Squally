////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "FireElemental.h"

#include "Resources/EntityResources.h"

const std::string FireElemental::MapKeyFireElemental = "fire-elemental";

FireElemental* FireElemental::deserialize(cocos2d::ValueMap& initProperties)
{
	FireElemental* instance = new FireElemental(initProperties);

	instance->autorelease();

	return instance;
}

FireElemental::FireElemental(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_FireElemental_Animations,
	EntityResources::Enemies_DaemonsHallow_FireElemental_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(820.0f, 1480.0f),
	0.20f,
	cocos2d::Vec2(64.0f, 0.0f),
	10,
	10)
{
}

FireElemental::~FireElemental()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
