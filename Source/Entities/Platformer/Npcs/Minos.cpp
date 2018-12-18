////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Minos.h"

#include "Resources/EntityResources.h"

const std::string Minos::MapKeyMinos = "minos";

Minos* Minos::deserialize(cocos2d::ValueMap* initProperties)
{
	Minos* instance = new Minos(initProperties);

	instance->autorelease();

	return instance;
}

Minos::Minos(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Minos_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Minos::~Minos()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
