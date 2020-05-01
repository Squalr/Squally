#include "Shopkeeper.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Shopkeeper::MapKey = "horse";

Shopkeeper* Shopkeeper::deserialize(ValueMap& properties)
{
	Shopkeeper* instance = new Shopkeeper(properties);

	instance->autorelease();

	return instance;
}

Shopkeeper::Shopkeeper(ValueMap& properties) : super(properties,
	Shopkeeper::MapKey,
	EntityResources::Misc_Tutorials_Shopkeeper_Animations,
	EntityResources::Misc_Tutorials_Shopkeeper_Emblem,
	Size(192.0f, 420.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Shopkeeper::~Shopkeeper()
{
}

Vec2 Shopkeeper::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Shopkeeper::getEntityName()
{
	return Strings::Common_Empty::create();
}
