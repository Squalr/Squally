////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Cyrogen.h"

#include "Resources/EntityResources.h"

const std::string Cyrogen::MapKeyCyrogen = "cyrogen";

Cyrogen* Cyrogen::deserialize(cocos2d::ValueMap* initProperties)
{
	Cyrogen* instance = new Cyrogen(initProperties);

	instance->autorelease();

	return instance;
}

Cyrogen::Cyrogen(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaPeaks_Cyrogen_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(420.0f, 420.0f),
	0.7f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Cyrogen::~Cyrogen()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
