////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "KingRedsong.h"

#include "Resources/EntityResources.h"

const std::string KingRedsong::MapKeyKingRedsong = "king-redsong";

KingRedsong* KingRedsong::deserialize(cocos2d::ValueMap* initProperties)
{
	KingRedsong* instance = new KingRedsong(initProperties);

	instance->autorelease();

	return instance;
}

KingRedsong::KingRedsong(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_CastleValgrind_KingRedsong_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(160.0f, 192.0f),
	1.0f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

KingRedsong::~KingRedsong()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
