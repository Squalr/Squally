////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Vampiress.h"

#include "Resources/EntityResources.h"

const std::string Vampiress::MapKeyVampiress = "vampiress";

Vampiress* Vampiress::deserialize(cocos2d::ValueMap* initProperties)
{
	Vampiress* instance = new Vampiress(initProperties);

	instance->autorelease();

	return instance;
}

Vampiress::Vampiress(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_Vampiress_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(96.0f, 236.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Vampiress::~Vampiress()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
