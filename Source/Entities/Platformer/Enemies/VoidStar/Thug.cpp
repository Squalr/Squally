////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Thug.h"

#include "Resources/EntityResources.h"

const std::string Thug::MapKeyThug = "thug";

Thug* Thug::deserialize(cocos2d::ValueMap& initProperties)
{
	Thug* instance = new Thug(initProperties);

	instance->autorelease();

	return instance;
}

Thug::Thug(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_Thug_Animations,
	EntityResources::Enemies_VoidStar_Thug_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 248.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Thug::~Thug()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
