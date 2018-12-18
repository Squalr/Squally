////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Rhinoman.h"

#include "Resources/EntityResources.h"

const std::string Rhinoman::MapKeyRhinoman = "rhinoman";

Rhinoman* Rhinoman::deserialize(cocos2d::ValueMap* initProperties)
{
	Rhinoman* instance = new Rhinoman(initProperties);

	instance->autorelease();

	return instance;
}

Rhinoman::Rhinoman(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_Rhinoman_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(592.0f, 592.0f),
	1.0f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Rhinoman::~Rhinoman()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
