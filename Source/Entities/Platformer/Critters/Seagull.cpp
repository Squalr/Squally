#include "Seagull.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Seagull::MapKey = "seagull";

Seagull* Seagull::deserialize(ValueMap& properties)
{
	Seagull* instance = new Seagull(properties);

	instance->autorelease();

	return instance;
}

Seagull::Seagull(ValueMap& properties) : super(properties,
	Seagull::MapKey,
	EntityResources::Misc_EndianForest_Seagull_Animations,
	EntityResources::Misc_EndianForest_Seagull_Emblem,
	Size(96.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Seagull::~Seagull()
{
}

Vec2 Seagull::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Seagull::getEntityName()
{
	return Strings::Platformer_Entities_Names_Critters_Seagull::create();
}
