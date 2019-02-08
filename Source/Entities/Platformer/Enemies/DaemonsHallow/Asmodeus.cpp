////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Asmodeus.h"

#include "Resources/EntityResources.h"

const std::string Asmodeus::MapKeyAsmodeus = "asmodeus";

Asmodeus* Asmodeus::deserialize(cocos2d::ValueMap& initProperties)
{
	Asmodeus* instance = new Asmodeus(initProperties);

	instance->autorelease();

	return instance;
}

Asmodeus::Asmodeus(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_Asmodeus_Animations,
	EntityResources::Enemies_DaemonsHallow_Asmodeus_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(480.0f, 480.0f),
	0.7f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Asmodeus::~Asmodeus()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
