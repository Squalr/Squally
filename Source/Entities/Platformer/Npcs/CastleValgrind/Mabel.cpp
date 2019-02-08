////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Mabel.h"

#include "Resources/EntityResources.h"

const std::string Mabel::MapKeyMabel = "mabel";

Mabel* Mabel::deserialize(cocos2d::ValueMap& initProperties)
{
	Mabel* instance = new Mabel(initProperties);

	instance->autorelease();

	return instance;
}

Mabel::Mabel(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_CastleValgrind_Mabel_Animations,
	EntityResources::Npcs_CastleValgrind_Mabel_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Mabel::~Mabel()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
