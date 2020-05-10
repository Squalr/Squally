#include "WaterElemental.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WaterElemental::MapKey = "water-elemental";

WaterElemental* WaterElemental::deserialize(ValueMap& properties)
{
	WaterElemental* instance = new WaterElemental(properties);

	instance->autorelease();

	return instance;
}

WaterElemental::WaterElemental(ValueMap& properties) : super(properties,
	WaterElemental::MapKey,
	EntityResources::Enemies_BalmerPeaks_WaterElemental_Animations,
	EntityResources::Enemies_BalmerPeaks_WaterElemental_Emblem,
	Size(820.0f, 1480.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

WaterElemental::~WaterElemental()
{
}

Vec2 WaterElemental::getDialogueOffset()
{
	return Vec2(-32.0f, -224.0f);
}

LocalizedString* WaterElemental::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BalmerPeaks_WaterElemental::create();
}
