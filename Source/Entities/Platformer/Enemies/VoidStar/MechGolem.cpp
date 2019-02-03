////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "MechGolem.h"

#include "Resources/EntityResources.h"

const std::string MechGolem::MapKeyMechGolem = "mech-golem";

MechGolem* MechGolem::deserialize(cocos2d::ValueMap* initProperties)
{
	MechGolem* instance = new MechGolem(initProperties);

	instance->autorelease();

	return instance;
}

MechGolem::MechGolem(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_MechGolem_Animations,
	EntityResources::Enemies_VoidStar_MechGolem_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(640.0f, 720.0f),
	0.7f,
	cocos2d::Vec2(-48.0f, 0.0f),
	10,
	10)
{
}

MechGolem::~MechGolem()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
