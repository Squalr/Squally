////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Exterminator.h"

#include "Resources/EntityResources.h"

const std::string Exterminator::MapKeyExterminator = "exterminator";

Exterminator* Exterminator::deserialize(cocos2d::ValueMap* initProperties)
{
	Exterminator* instance = new Exterminator(initProperties);

	instance->autorelease();

	return instance;
}

Exterminator::Exterminator(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_Exterminator_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(320.0f, 278.0f),
	1.0f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Exterminator::~Exterminator()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
