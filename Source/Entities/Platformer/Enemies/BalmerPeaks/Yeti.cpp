////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Yeti.h"

#include "Resources/EntityResources.h"

const std::string Yeti::MapKeyYeti = "yeti";

Yeti* Yeti::deserialize(cocos2d::ValueMap* initProperties)
{
	Yeti* instance = new Yeti(initProperties);

	instance->autorelease();

	return instance;
}

Yeti::Yeti(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_Yeti_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(380.0f, 572.0f),
	0.4f,
	cocos2d::Vec2(24.0f, 0.0f),
	10,
	10)
{
}

Yeti::~Yeti()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
