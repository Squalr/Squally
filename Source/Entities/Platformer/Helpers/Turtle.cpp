////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Turtle.h"

#include "Resources/EntityResources.h"

const std::string Turtle::MapKeyTurtle = "turtle";

Turtle* Turtle::deserialize(cocos2d::ValueMap& initProperties)
{
	Turtle* instance = new Turtle(initProperties);

	instance->autorelease();

	return instance;
}

Turtle::Turtle(cocos2d::ValueMap& initProperties) : PlatformerEntity(initProperties,
	EntityResources::Helpers_Turtle_Animations,
	EntityResources::Helpers_Turtle_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(224.0f, 440.0f),
	0.3f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Turtle::~Turtle()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
