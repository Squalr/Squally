////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Cypress.h"

#include "Resources/EntityResources.h"

const std::string Cypress::MapKeyCypress = "cypress";

Cypress* Cypress::deserialize(cocos2d::ValueMap* initProperties)
{
	Cypress* instance = new Cypress(initProperties);

	instance->autorelease();

	return instance;
}

Cypress::Cypress(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_SeaSharpCaverns_Cypress_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Cypress::~Cypress()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
