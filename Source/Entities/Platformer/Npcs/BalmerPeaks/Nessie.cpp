////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Nessie.h"

#include "Resources/EntityResources.h"

const std::string Nessie::MapKeyNessie = "nessie";

Nessie* Nessie::deserialize(cocos2d::ValueMap* initProperties)
{
	Nessie* instance = new Nessie(initProperties);

	instance->autorelease();

	return instance;
}

Nessie::Nessie(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_BalmerPeaks_Nessie_Animations,
	EntityResources::Npcs_BalmerPeaks_Nessie_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Nessie::~Nessie()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
