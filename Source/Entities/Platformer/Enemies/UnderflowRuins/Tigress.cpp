////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Tigress.h"

#include "Resources/EntityResources.h"

const std::string Tigress::MapKeyTigress = "tigress";

Tigress* Tigress::deserialize(cocos2d::ValueMap* initProperties)
{
	Tigress* instance = new Tigress(initProperties);

	instance->autorelease();

	return instance;
}

Tigress::Tigress(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_Tigress_Animations,
	EntityResources::Enemies_UnderflowRuins_Tigress_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(128.0f, 256.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Tigress::~Tigress()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
