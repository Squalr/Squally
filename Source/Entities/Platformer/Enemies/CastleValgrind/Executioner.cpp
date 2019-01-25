////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Executioner.h"

#include "Resources/EntityResources.h"

const std::string Executioner::MapKeyExecutioner = "executioner";

Executioner* Executioner::deserialize(cocos2d::ValueMap* initProperties)
{
	Executioner* instance = new Executioner(initProperties);

	instance->autorelease();

	return instance;
}

Executioner::Executioner(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_Executioner_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(112.0f, 820.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Executioner::~Executioner()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
