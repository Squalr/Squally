////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Piper.h"

#include "Resources/EntityResources.h"

const std::string Piper::MapKeyPiper = "piper";

Piper* Piper::deserialize(cocos2d::ValueMap* initProperties)
{
	Piper* instance = new Piper(initProperties);

	instance->autorelease();

	return instance;
}

Piper::Piper(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_VoidStar_Piper_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Piper::~Piper()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
