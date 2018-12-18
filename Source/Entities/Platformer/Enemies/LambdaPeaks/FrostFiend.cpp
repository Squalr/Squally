////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "FrostFiend.h"

#include "Resources/EntityResources.h"

const std::string FrostFiend::MapKeyFrostFiend = "frost-fiend";

FrostFiend* FrostFiend::deserialize(cocos2d::ValueMap* initProperties)
{
	FrostFiend* instance = new FrostFiend(initProperties);

	instance->autorelease();

	return instance;
}

FrostFiend::FrostFiend(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaPeaks_FrostFiend_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(212.0f, 296.0f),
	0.7f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

FrostFiend::~FrostFiend()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
