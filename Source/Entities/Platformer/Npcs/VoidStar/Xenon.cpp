////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Xenon.h"

#include "Resources/EntityResources.h"

const std::string Xenon::MapKeyXenon = "xenon";

Xenon* Xenon::deserialize(cocos2d::ValueMap* initProperties)
{
	Xenon* instance = new Xenon(initProperties);

	instance->autorelease();

	return instance;
}

Xenon::Xenon(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_VoidStar_Xenon_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Xenon::~Xenon()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
