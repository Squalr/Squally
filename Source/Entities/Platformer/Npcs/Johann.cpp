////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Johann.h"

#include "Resources/EntityResources.h"

const std::string Johann::MapKeyJohann = "johann";

Johann* Johann::deserialize(cocos2d::ValueMap* initProperties)
{
	Johann* instance = new Johann(initProperties);

	instance->autorelease();

	return instance;
}

Johann::Johann(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_Johann_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Johann::~Johann()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
