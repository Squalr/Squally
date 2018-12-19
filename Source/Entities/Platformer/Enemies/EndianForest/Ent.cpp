////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Ent.h"

#include "Resources/EntityResources.h"

const std::string Ent::MapKeyEnt = "ent";

Ent* Ent::deserialize(cocos2d::ValueMap* initProperties)
{
	Ent* instance = new Ent(initProperties);

	instance->autorelease();

	return instance;
}

Ent::Ent(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_Ent_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(512.0f, 960.0f),
	1.0f,
	cocos2d::Vec2(24.0f, -452.0f))
{
}

Ent::~Ent()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
