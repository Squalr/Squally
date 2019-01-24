////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "IceGolem.h"

#include "Resources/EntityResources.h"

const std::string IceGolem::MapKeyIceGolem = "ice-golem";

IceGolem* IceGolem::deserialize(cocos2d::ValueMap* initProperties)
{
	IceGolem* instance = new IceGolem(initProperties);

	instance->autorelease();

	return instance;
}

IceGolem::IceGolem(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaPeaks_IceGolem_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(1680.0f, 996.0f),
	0.35f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

IceGolem::~IceGolem()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
