////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Atreus.h"

#include "Resources/EntityResources.h"

const std::string Atreus::MapKeyAtreus = "atreus";

Atreus* Atreus::deserialize(cocos2d::ValueMap* initProperties)
{
	Atreus* instance = new Atreus(initProperties);

	instance->autorelease();

	return instance;
}

Atreus::Atreus(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_VoidStar_Atreus_Animations,
	EntityResources::Npcs_VoidStar_Atreus_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Atreus::~Atreus()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
