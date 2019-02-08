////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Shade.h"

#include "Resources/EntityResources.h"

const std::string Shade::MapKeyShade = "shade";

Shade* Shade::deserialize(cocos2d::ValueMap& initProperties)
{
	Shade* instance = new Shade(initProperties);

	instance->autorelease();

	return instance;
}

Shade::Shade(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_Shade_Animations,
	EntityResources::Enemies_CastleValgrind_Shade_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(196.0f, 512.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Shade::~Shade()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
