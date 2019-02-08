////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Olive.h"

#include "Resources/EntityResources.h"

const std::string Olive::MapKeyOlive = "olive";

Olive* Olive::deserialize(cocos2d::ValueMap& initProperties)
{
	Olive* instance = new Olive(initProperties);

	instance->autorelease();

	return instance;
}

Olive::Olive(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_SeaSharpCaverns_Olive_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Olive_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Olive::~Olive()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
