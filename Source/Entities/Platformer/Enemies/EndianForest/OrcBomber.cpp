//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OrcBomber.h"

#include "Resources/EntityResources.h"

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////A////A////A////A////A////A////A////A////A////A/

#include "Scenes/Maps/Platformer/Combat/Attacks/Basic/BasicSlash.h"
#include "Scenes/Maps/Platformer/Combat/Attacks/OrcBomber/TorchThrow.h"

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

const std::string OrcBomber::MapKeyOrcBomber = "orc-bomber";

OrcBomber* OrcBomber::deserialize(cocos2d::ValueMap& initProperties)
{
	OrcBomber* instance = new OrcBomber(initProperties);

	instance->autorelease();

	return instance;
}

OrcBomber::OrcBomber(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_OrcBomber_Animations,
	EntityResources::Enemies_EndianForest_OrcBomber_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 218.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	//this->registerAttack(BasicSlash::create(0.7f, 0.2f));
	this->registerAttack(TorchThrow::create(0.7f, 5.0f));

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

OrcBomber::~OrcBomber()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
