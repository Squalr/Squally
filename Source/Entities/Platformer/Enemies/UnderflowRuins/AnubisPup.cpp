////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "AnubisPup.h"

#include "Resources/EntityResources.h"

const std::string AnubisPup::MapKeyAnubisPup = "anubis-pup";

AnubisPup* AnubisPup::deserialize(cocos2d::ValueMap* initProperties)
{
	AnubisPup* instance = new AnubisPup(initProperties);

	instance->autorelease();

	return instance;
}

AnubisPup::AnubisPup(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_AnubisPup_Animations,
	EntityResources::Enemies_UnderflowRuins_AnubisPup_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(128.0f, 186.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

AnubisPup::~AnubisPup()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
