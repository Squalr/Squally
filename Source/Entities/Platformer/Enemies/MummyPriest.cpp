////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "MummyPriest.h"

#include "Resources/EntityResources.h"

const std::string MummyPriest::MapKeyMummyPriest = "mummy-priest";

MummyPriest* MummyPriest::deserialize(cocos2d::ValueMap* initProperties)
{
	MummyPriest* instance = new MummyPriest(initProperties);

	instance->autorelease();

	return instance;
}

MummyPriest::MummyPriest(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_MummyPriest_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(128.0f, 256.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

MummyPriest::~MummyPriest()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
