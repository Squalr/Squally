////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "KingZul.h"

#include "Resources/EntityResources.h"

const std::string KingZul::MapKeyKingZul = "king-zul";

KingZul* KingZul::deserialize(cocos2d::ValueMap* initProperties)
{
	KingZul* instance = new KingZul(initProperties);

	instance->autorelease();

	return instance;
}

KingZul::KingZul(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_KingZul_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(196.0f, 320.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

KingZul::~KingZul()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
