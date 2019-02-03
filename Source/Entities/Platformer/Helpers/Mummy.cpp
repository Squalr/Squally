////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Mummy.h"

#include "Resources/EntityResources.h"

const std::string Mummy::MapKeyMummy = "mummy";

Mummy* Mummy::deserialize(cocos2d::ValueMap* initProperties)
{
	Mummy* instance = new Mummy(initProperties);

	instance->autorelease();

	return instance;
}

Mummy::Mummy(cocos2d::ValueMap* initProperties) : PlatformerEntity(initProperties,
	EntityResources::Helpers_Mummy_Animations,
	EntityResources::Helpers_Mummy_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(224.0f, 440.0f),
	0.3f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Mummy::~Mummy()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
