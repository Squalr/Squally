////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Zelina.h"

#include "Resources/EntityResources.h"

const std::string Zelina::MapKeyZelina = "zelina";

Zelina* Zelina::deserialize(cocos2d::ValueMap& initProperties)
{
	Zelina* instance = new Zelina(initProperties);

	instance->autorelease();

	return instance;
}

Zelina::Zelina(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_LambdaCrypts_Zelina_Animations,
	EntityResources::Npcs_LambdaCrypts_Zelina_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Zelina::~Zelina()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
