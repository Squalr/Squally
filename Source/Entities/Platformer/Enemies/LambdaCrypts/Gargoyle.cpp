////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Gargoyle.h"

#include "Resources/EntityResources.h"

const std::string Gargoyle::MapKeyGargoyle = "gargoyle";

Gargoyle* Gargoyle::deserialize(cocos2d::ValueMap* initProperties)
{
	Gargoyle* instance = new Gargoyle(initProperties);

	instance->autorelease();

	return instance;
}

Gargoyle::Gargoyle(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_Gargoyle_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 256.0f),
	0.9f,
	cocos2d::Vec2(-32.0f, 0.0f),
	10,
	10)
{
}

Gargoyle::~Gargoyle()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
