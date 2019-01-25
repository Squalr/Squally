////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "VoidArcher.h"

#include "Resources/EntityResources.h"

const std::string VoidArcher::MapKeyVoidArcher = "void-archer";

VoidArcher* VoidArcher::deserialize(cocos2d::ValueMap* initProperties)
{
	VoidArcher* instance = new VoidArcher(initProperties);

	instance->autorelease();

	return instance;
}

VoidArcher::VoidArcher(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_VoidArcher_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(196.0f, 348.0f),
	0.65f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

VoidArcher::~VoidArcher()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
