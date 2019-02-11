//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "PrincessPepper.h"

#include "Resources/EntityResources.h"

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////A////A////A////A////A////A////A////A////A////A/

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

const std::string PrincessPepper::MapKeyPrincessPepper = "princess-pepper";

PrincessPepper* PrincessPepper::deserialize(cocos2d::ValueMap& initProperties)
{
	PrincessPepper* instance = new PrincessPepper(initProperties);

	instance->autorelease();

	return instance;
}

PrincessPepper::PrincessPepper(cocos2d::ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_BalmerPeaks_PrincessPepper_Animations,
	EntityResources::Npcs_BalmerPeaks_PrincessPepper_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
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

PrincessPepper::~PrincessPepper()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
