//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "AnubisWarrior.h"

#include "Resources/EntityResources.h"

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////A////A////A////A////A////A////A////A////A////A/

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

const std::string AnubisWarrior::MapKeyAnubisWarrior = "anubis-warrior";

AnubisWarrior* AnubisWarrior::deserialize(cocos2d::ValueMap& initProperties)
{
	AnubisWarrior* instance = new AnubisWarrior(initProperties);

	instance->autorelease();

	return instance;
}

AnubisWarrior::AnubisWarrior(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_AnubisWarrior_Animations,
	EntityResources::Enemies_UnderflowRuins_AnubisWarrior_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 292.0f),
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

AnubisWarrior::~AnubisWarrior()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
