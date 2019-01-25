////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "MechDog.h"

#include "Resources/EntityResources.h"

const std::string MechDog::MapKeyMechDog = "mech-dog";

MechDog* MechDog::deserialize(cocos2d::ValueMap* initProperties)
{
	MechDog* instance = new MechDog(initProperties);

	instance->autorelease();

	return instance;
}

MechDog::MechDog(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_MechDog_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(540.0f, 340.0f),
	0.7f,
	cocos2d::Vec2(-64.0f, 0.0f),
	10,
	10)
{
}

MechDog::~MechDog()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
