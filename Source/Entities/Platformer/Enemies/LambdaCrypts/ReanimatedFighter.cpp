//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ReanimatedFighter.h"

#include "Resources/EntityResources.h"

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////A////A////A////A////A////A////A////A////A////A/

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

const std::string ReanimatedFighter::MapKeyReanimatedFighter = "reanimated-fighter";

ReanimatedFighter* ReanimatedFighter::deserialize(cocos2d::ValueMap& initProperties)
{
	ReanimatedFighter* instance = new ReanimatedFighter(initProperties);

	instance->autorelease();

	return instance;
}

ReanimatedFighter::ReanimatedFighter(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_ReanimatedFighter_Animations,
	EntityResources::Enemies_LambdaCrypts_ReanimatedFighter_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 248.0f),
	0.9f,
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

ReanimatedFighter::~ReanimatedFighter()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
