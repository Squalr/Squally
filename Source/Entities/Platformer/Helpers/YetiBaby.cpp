////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "YetiBaby.h"

#include "Resources/EntityResources.h"

const std::string YetiBaby::MapKeyYetiBaby = "yeti-baby";

YetiBaby* YetiBaby::deserialize(cocos2d::ValueMap* initProperties)
{
	YetiBaby* instance = new YetiBaby(initProperties);

	instance->autorelease();

	return instance;
}

YetiBaby::YetiBaby(cocos2d::ValueMap* initProperties) : PlatformerEntity(initProperties,
	EntityResources::Helpers_YetiBaby_Animations,
	EntityResources::Helpers_YetiBaby_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	1.0f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

YetiBaby::~YetiBaby()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
