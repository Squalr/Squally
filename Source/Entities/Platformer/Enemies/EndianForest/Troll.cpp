#include "Troll.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Troll::MapKeyTroll = "troll";

Troll* Troll::deserialize(ValueMap& properties)
{
	Troll* instance = new Troll(properties);

	instance->autorelease();

	return instance;
}

Troll::Troll(ValueMap& properties) : super(properties,
	Troll::MapKeyTroll,
	EntityResources::Enemies_EndianForest_Troll_Animations,
	EntityResources::Enemies_EndianForest_Troll_Emblem,
	Size(256.0f, 248.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Troll::~Troll()
{
}

Vec2 Troll::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Troll::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_Troll::create();
}
