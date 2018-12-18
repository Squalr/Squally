////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "EvilEye.h"

#include "Resources/EntityResources.h"

const std::string EvilEye::MapKeyEvilEye = "evil-eye";

EvilEye* EvilEye::deserialize(cocos2d::ValueMap* initProperties)
{
	EvilEye* instance = new EvilEye(initProperties);

	instance->autorelease();

	return instance;
}

EvilEye::EvilEye(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_EvilEye_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(720.0f, 840.0f),
	0.6f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

EvilEye::~EvilEye()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
