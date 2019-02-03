////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Mara.h"

#include "Resources/EntityResources.h"

const std::string Mara::MapKeyMara = "mara";

Mara* Mara::deserialize(cocos2d::ValueMap* initProperties)
{
	Mara* instance = new Mara(initProperties);

	instance->autorelease();

	return instance;
}

Mara::Mara(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_VoidStar_Mara_Animations,
	EntityResources::Npcs_VoidStar_Mara_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Mara::~Mara()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
