////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Viper.h"

#include "Resources/EntityResources.h"

const std::string Viper::MapKeyViper = "viper";

Viper* Viper::deserialize(cocos2d::ValueMap* initProperties)
{
	Viper* instance = new Viper(initProperties);

	instance->autorelease();

	return instance;
}

Viper::Viper(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_LexiconCrypts_Viper_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(472.0f, 780.0f),
	0.3f,
	cocos2d::Vec2(-24.0f, -390.0f))
{
}

Viper::~Viper()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
