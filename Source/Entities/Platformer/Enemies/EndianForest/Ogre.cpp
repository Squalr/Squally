////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Ogre.h"

#include "Entities/Platformer/Attacks/Basic/BasicSlash.h"

#include "Resources/EntityResources.h"

const std::string Ogre::MapKeyOgre = "ogre";

Ogre* Ogre::deserialize(cocos2d::ValueMap& initProperties)
{
	Ogre* instance = new Ogre(initProperties);

	instance->autorelease();

	return instance;
}

Ogre::Ogre(cocos2d::ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_Ogre_Animations,
	EntityResources::Enemies_EndianForest_Ogre_Emblem,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(256.0f, 248.0f),
	1.0f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->registerAttack(BasicSlash::create());
}

Ogre::~Ogre()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
