////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "MechGuard.h"

#include "Resources/EntityResources.h"

const std::string MechGuard::MapKeyMechGuard = "mech-guard";

MechGuard* MechGuard::deserialize(cocos2d::ValueMap* initProperties)
{
	MechGuard* instance = new MechGuard(initProperties);

	instance->autorelease();

	return instance;
}

MechGuard::MechGuard(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_MechGuard_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(112.0f, 596.0f),
	0.9f,
	cocos2d::Vec2(0.0f, -298.0f),
	10,
	10)
{
}

MechGuard::~MechGuard()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
