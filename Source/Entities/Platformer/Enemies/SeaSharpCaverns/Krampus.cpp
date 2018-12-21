////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Krampus.h"

#include "Resources/EntityResources.h"

const std::string Krampus::MapKeyKrampus = "krampus";

Krampus* Krampus::deserialize(cocos2d::ValueMap* initProperties)
{
	Krampus* instance = new Krampus(initProperties);

	instance->autorelease();

	return instance;
}

Krampus::Krampus(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_Krampus_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(396.0f, 412.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Krampus::~Krampus()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
