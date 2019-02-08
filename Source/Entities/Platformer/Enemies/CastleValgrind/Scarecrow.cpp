////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Scarecrow.h"

#include "Resources/EntityResources.h"

const std::string Scarecrow::MapKeyScarecrow = "scarecrow";

Scarecrow* Scarecrow::deserialize(cocos2d::ValueMap& initProperties)
{
	Scarecrow* instance = new Scarecrow(initProperties);

	instance->autorelease();

	return instance;
}

Scarecrow::Scarecrow(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_Scarecrow_Animations,
	EntityResources::Enemies_CastleValgrind_Scarecrow_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(196.0f, 512.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Scarecrow::~Scarecrow()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
