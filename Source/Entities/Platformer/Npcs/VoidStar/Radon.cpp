////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Radon.h"

#include "Resources/EntityResources.h"

const std::string Radon::MapKeyRadon = "radon";

Radon* Radon::deserialize(cocos2d::ValueMap& initProperties)
{
	Radon* instance = new Radon(initProperties);

	instance->autorelease();

	return instance;
}

Radon::Radon(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_VoidStar_Radon_Animations,
	EntityResources::Npcs_VoidStar_Radon_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Radon::~Radon()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
