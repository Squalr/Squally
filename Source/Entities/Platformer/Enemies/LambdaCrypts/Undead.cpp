////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Undead.h"

#include "Resources/EntityResources.h"

const std::string Undead::MapKeyUndead = "undead";

Undead* Undead::deserialize(cocos2d::ValueMap& initProperties)
{
	Undead* instance = new Undead(initProperties);

	instance->autorelease();

	return instance;
}

Undead::Undead(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_Undead_Animations,
	EntityResources::Enemies_LambdaCrypts_Undead_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(146.0f, 248.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Undead::~Undead()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
