#include "Ogre.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ogre::MapKeyOgre = "ogre";

Ogre* Ogre::deserialize(ValueMap& properties)
{
	Ogre* instance = new Ogre(properties);

	instance->autorelease();

	return instance;
}

Ogre::Ogre(ValueMap& properties) : super(properties,
	Ogre::MapKeyOgre,
	EntityResources::Enemies_EndianForest_Ogre_Animations,
	EntityResources::Enemies_EndianForest_Ogre_Emblem,
	Size(256.0f, 248.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Ogre::~Ogre()
{
}

Vec2 Ogre::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ogre::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_Ogre::create();
}
