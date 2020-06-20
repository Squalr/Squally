#include "Pan.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Pan::MapKey = "pan";

Pan* Pan::deserialize(ValueMap& properties)
{
	Pan* instance = new Pan(properties);

	instance->autorelease();

	return instance;
}

Pan::Pan(ValueMap& properties) : super(properties,
	Pan::MapKey,
	EntityResources::Npcs_DaemonsHallow_Pan_Animations,
	EntityResources::Npcs_DaemonsHallow_Pan_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Pan::~Pan()
{
}

Vec2 Pan::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Pan::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Pan::create();
}
