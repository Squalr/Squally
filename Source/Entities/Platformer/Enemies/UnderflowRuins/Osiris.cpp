////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Osiris.h"

#include "Resources/EntityResources.h"

const std::string Osiris::MapKeyOsiris = "osiris";

Osiris* Osiris::deserialize(cocos2d::ValueMap& initProperties)
{
	Osiris* instance = new Osiris(initProperties);

	instance->autorelease();

	return instance;
}

Osiris::Osiris(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_Osiris_Animations,
	EntityResources::Enemies_UnderflowRuins_Osiris_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(324.0f, 316.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Osiris::~Osiris()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
