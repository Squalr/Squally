#include "Cyclops.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Cyclops::MapKeyCyclops = "cyclops";

Cyclops* Cyclops::deserialize(ValueMap& properties)
{
	Cyclops* instance = new Cyclops(properties);

	instance->autorelease();

	return instance;
}

Cyclops::Cyclops(ValueMap& properties) : super(properties,
	Cyclops::MapKeyCyclops,
	EntityResources::Enemies_EndianForest_Cyclops_Animations,
	EntityResources::Enemies_EndianForest_Cyclops_Emblem,
	Size(296.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Cyclops::~Cyclops()
{
}

Vec2 Cyclops::getDialogueOffset()
{
	return Vec2(-32.0f, -196.0f);
}

LocalizedString* Cyclops::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_Cyclops::create();
}
