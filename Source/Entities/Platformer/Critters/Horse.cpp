#include "Horse.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Horse::MapKeyHorse = "horse";

Horse* Horse::deserialize(ValueMap& properties)
{
	Horse* instance = new Horse(properties);

	instance->autorelease();

	return instance;
}

Horse::Horse(ValueMap& properties) : super(properties,
	Horse::MapKeyHorse,
	EntityResources::Misc_EndianForest_Horse_Animations,
	EntityResources::Misc_EndianForest_Horse_Emblem,
	Size(192.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Horse::~Horse()
{
}

Vec2 Horse::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Horse::getEntityName()
{
	return Strings::Platformer_Entities_Names_Critters_Horse::create();
}
