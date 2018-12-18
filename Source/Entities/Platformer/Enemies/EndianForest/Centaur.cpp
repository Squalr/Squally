////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Centaur.h"

#include "Resources/EntityResources.h"

const std::string Centaur::MapKeyCentaur = "centaur";

Centaur* Centaur::deserialize(cocos2d::ValueMap* initProperties)
{
	Centaur* instance = new Centaur(initProperties);

	instance->autorelease();

	return instance;
}

Centaur::Centaur(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_Centaur_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(296.0f, 256.0f),
	1.0f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Centaur::~Centaur()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
