////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Kringle.h"

#include "Resources/EntityResources.h"

const std::string Kringle::MapKeyKringle = "kringle";

Kringle* Kringle::deserialize(cocos2d::ValueMap* initProperties)
{
	Kringle* instance = new Kringle(initProperties);

	instance->autorelease();

	return instance;
}

Kringle::Kringle(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_BalmerPeaks_Kringle_Animations,
	EntityResources::Npcs_BalmerPeaks_Kringle_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Kringle::~Kringle()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
