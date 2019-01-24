////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Viking.h"

#include "Resources/EntityResources.h"

const std::string Viking::MapKeyViking = "viking";

Viking* Viking::deserialize(cocos2d::ValueMap* initProperties)
{
	Viking* instance = new Viking(initProperties);

	instance->autorelease();

	return instance;
}

Viking::Viking(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_Viking_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(284.0f, 256.0f),
	0.9f,
	cocos2d::Vec2(0.0f, -112.0f),
	10,
	10)
{
}

Viking::~Viking()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
