////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Wraith.h"

#include "Resources/EntityResources.h"

const std::string Wraith::MapKeyWraith = "wraith";

Wraith* Wraith::deserialize(cocos2d::ValueMap* initProperties)
{
	Wraith* instance = new Wraith(initProperties);

	instance->autorelease();

	return instance;
}

Wraith::Wraith(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_Wraith_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(142.0f, 400.0f),
	0.5f,
	cocos2d::Vec2(0.0f, 40.0f))
{
}

Wraith::~Wraith()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
