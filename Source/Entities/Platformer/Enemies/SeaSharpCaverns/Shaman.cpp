////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Shaman.h"

#include "Resources/EntityResources.h"

const std::string Shaman::MapKeyShaman = "shaman";

Shaman* Shaman::deserialize(cocos2d::ValueMap& initProperties)
{
	Shaman* instance = new Shaman(initProperties);

	instance->autorelease();

	return instance;
}

Shaman::Shaman(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_Shaman_Animations,
	EntityResources::Enemies_SeaSharpCaverns_Shaman_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 288.0f),
	0.75f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Shaman::~Shaman()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
