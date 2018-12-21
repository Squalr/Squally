////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "KingGrogg.h"

#include "Resources/EntityResources.h"

const std::string KingGrogg::MapKeyKingGrogg = "king-grogg";

KingGrogg* KingGrogg::deserialize(cocos2d::ValueMap* initProperties)
{
	KingGrogg* instance = new KingGrogg(initProperties);

	instance->autorelease();

	return instance;
}

KingGrogg::KingGrogg(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_KingGrogg_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(412.0f, 412.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

KingGrogg::~KingGrogg()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
