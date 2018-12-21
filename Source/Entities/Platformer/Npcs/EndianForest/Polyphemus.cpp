////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Polyphemus.h"

#include "Resources/EntityResources.h"

const std::string Polyphemus::MapKeyPolyphemus = "polyphemus";

Polyphemus* Polyphemus::deserialize(cocos2d::ValueMap* initProperties)
{
	Polyphemus* instance = new Polyphemus(initProperties);

	instance->autorelease();

	return instance;
}

Polyphemus::Polyphemus(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_Polyphemus_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Polyphemus::~Polyphemus()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
