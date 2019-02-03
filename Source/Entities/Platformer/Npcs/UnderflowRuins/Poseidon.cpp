////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Poseidon.h"

#include "Resources/EntityResources.h"

const std::string Poseidon::MapKeyPoseidon = "poseidon";

Poseidon* Poseidon::deserialize(cocos2d::ValueMap* initProperties)
{
	Poseidon* instance = new Poseidon(initProperties);

	instance->autorelease();

	return instance;
}

Poseidon::Poseidon(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_UnderflowRuins_Poseidon_Animations,
	EntityResources::Npcs_UnderflowRuins_Poseidon_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Poseidon::~Poseidon()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
