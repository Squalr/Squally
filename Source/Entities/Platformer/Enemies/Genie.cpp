////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Genie.h"

#include "Resources/EntityResources.h"

const std::string Genie::MapKeyGenie = "genie";

Genie* Genie::deserialize(cocos2d::ValueMap* initProperties)
{
	Genie* instance = new Genie(initProperties);

	instance->autorelease();

	return instance;
}

Genie::Genie(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_Genie_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(512.0f, 1126.0f),
	0.20f,
	cocos2d::Vec2(0.0f, -356.0f))
{
}

Genie::~Genie()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
