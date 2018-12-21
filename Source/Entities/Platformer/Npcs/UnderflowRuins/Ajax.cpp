////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Ajax.h"

#include "Resources/EntityResources.h"

const std::string Ajax::MapKeyAjax = "ajax";

Ajax* Ajax::deserialize(cocos2d::ValueMap* initProperties)
{
	Ajax* instance = new Ajax(initProperties);

	instance->autorelease();

	return instance;
}

Ajax::Ajax(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_UnderflowRuins_Ajax_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Ajax::~Ajax()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
