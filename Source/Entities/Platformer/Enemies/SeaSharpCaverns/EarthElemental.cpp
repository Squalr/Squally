#include "EarthElemental.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EarthElemental::MapKey = "earth-elemental";

EarthElemental* EarthElemental::deserialize(ValueMap& properties)
{
	EarthElemental* instance = new EarthElemental(properties);

	instance->autorelease();

	return instance;
}

EarthElemental::EarthElemental(ValueMap& properties) : super(properties,
	EarthElemental::MapKey,
	EntityResources::Enemies_SeaSharpCaverns_EarthElemental_Animations,
	EntityResources::Enemies_SeaSharpCaverns_EarthElemental_Emblem,
	Size(820.0f, 1480.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

EarthElemental::~EarthElemental()
{
}

Vec2 EarthElemental::getDialogueOffset()
{
	return Vec2(-32.0f, -224.0f);
}

LocalizedString* EarthElemental::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_EarthElemental::create();
}
