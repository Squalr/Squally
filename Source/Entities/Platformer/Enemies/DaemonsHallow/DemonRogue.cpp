////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "DemonRogue.h"

#include "Resources/EntityResources.h"

const std::string DemonRogue::MapKeyDemonRogue = "demon-rogue";

DemonRogue* DemonRogue::deserialize(cocos2d::ValueMap* initProperties)
{
	DemonRogue* instance = new DemonRogue(initProperties);

	instance->autorelease();

	return instance;
}

DemonRogue::DemonRogue(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonRogue_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(212.0f, 268.0f),
	0.65f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

DemonRogue::~DemonRogue()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
