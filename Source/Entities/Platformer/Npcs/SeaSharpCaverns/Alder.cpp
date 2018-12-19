////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Alder.h"

#include "Resources/EntityResources.h"

const std::string Alder::MapKeyAlder = "alder";

Alder* Alder::deserialize(cocos2d::ValueMap* initProperties)
{
	Alder* instance = new Alder(initProperties);

	instance->autorelease();

	return instance;
}

Alder::Alder(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_SeaSharpCaverns_Alder_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	1.0f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Alder::~Alder()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
