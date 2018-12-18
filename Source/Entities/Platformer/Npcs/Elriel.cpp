////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Elriel.h"

#include "Resources/EntityResources.h"

const std::string Elriel::MapKeyElriel = "elriel";

Elriel* Elriel::deserialize(cocos2d::ValueMap* initProperties)
{
	Elriel* instance = new Elriel(initProperties);

	instance->autorelease();

	return instance;
}

Elriel::Elriel(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Elriel_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Elriel::~Elriel()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
