#include "Ogre.h"

const std::string Ogre::MapKeyEnemyOgre = "ogre";

Ogre* Ogre::deserialize(ValueMap* initProperties)
{
	Ogre* instance = new Ogre(initProperties);

	instance->autorelease();

	return instance;
}

Ogre::Ogre(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Forest_Enemies_Ogre_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 248.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Ogre::~Ogre()
{
}
