////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "VampireLord.h"

#include "Resources/EntityResources.h"

const std::string VampireLord::MapKeyVampireLord = "vampire-lord";

VampireLord* VampireLord::deserialize(cocos2d::ValueMap* initProperties)
{
	VampireLord* instance = new VampireLord(initProperties);

	instance->autorelease();

	return instance;
}

VampireLord::VampireLord(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_VampireLord_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(240.0f, 312.0f),
	1.0f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

VampireLord::~VampireLord()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
