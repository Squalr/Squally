//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Turtle.h"

#include "Resources/EntityResources.h"

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////A////A////A////A////A////A////A////A////A////A/

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

const std::string Turtle::MapKeyTurtle = "turtle";

Turtle* Turtle::deserialize(cocos2d::ValueMap& initProperties)
{
	Turtle* instance = new Turtle(initProperties);

	instance->autorelease();

	return instance;
}

Turtle::Turtle(cocos2d::ValueMap& initProperties) : PlatformerEntity(initProperties,
	EntityResources::Helpers_EndianForest_Turtle_Animations,
	EntityResources::Helpers_EndianForest_Turtle_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(224.0f, 440.0f),
	0.3f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
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
