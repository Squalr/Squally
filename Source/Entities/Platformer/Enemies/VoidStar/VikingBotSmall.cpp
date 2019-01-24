////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "VikingBotSmall.h"

#include "Resources/EntityResources.h"

const std::string VikingBotSmall::MapKeyVikingBotSmall = "viking-bot-small";

VikingBotSmall* VikingBotSmall::deserialize(cocos2d::ValueMap* initProperties)
{
	VikingBotSmall* instance = new VikingBotSmall(initProperties);

	instance->autorelease();

	return instance;
}

VikingBotSmall::VikingBotSmall(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_VikingBotSmall_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(768.0f, 768.0f),
	0.25f,
	cocos2d::Vec2(0.0f, 160.0f),
	10,
	10)
{
}

VikingBotSmall::~VikingBotSmall()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
