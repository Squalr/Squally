////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Lioness.h"

#include "Resources/EntityResources.h"

const std::string Lioness::MapKeyLioness = "lioness";

Lioness* Lioness::deserialize(cocos2d::ValueMap* initProperties)
{
	Lioness* instance = new Lioness(initProperties);

	instance->autorelease();

	return instance;
}

Lioness::Lioness(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_Lioness_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(128.0f, 278.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Lioness::~Lioness()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
