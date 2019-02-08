////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Barbarian.h"

#include "Resources/EntityResources.h"

const std::string Barbarian::MapKeyBarbarian = "barbarian";

Barbarian* Barbarian::deserialize(cocos2d::ValueMap& initProperties)
{
	Barbarian* instance = new Barbarian(initProperties);

	instance->autorelease();

	return instance;
}

Barbarian::Barbarian(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_Barbarian_Animations,
	EntityResources::Enemies_VoidStar_Barbarian_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(278.0f, 288.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Barbarian::~Barbarian()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
