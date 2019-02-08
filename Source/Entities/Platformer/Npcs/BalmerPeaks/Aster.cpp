////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Aster.h"

#include "Resources/EntityResources.h"

const std::string Aster::MapKeyAster = "aster";

Aster* Aster::deserialize(cocos2d::ValueMap& initProperties)
{
	Aster* instance = new Aster(initProperties);

	instance->autorelease();

	return instance;
}

Aster::Aster(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_BalmerPeaks_Aster_Animations,
	EntityResources::Npcs_BalmerPeaks_Aster_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Aster::~Aster()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
