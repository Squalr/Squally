#include "FireElemental.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FireElemental::MapKey = "fire-elemental";

FireElemental* FireElemental::deserialize(ValueMap& properties)
{
	FireElemental* instance = new FireElemental(properties);

	instance->autorelease();

	return instance;
}

FireElemental::FireElemental(ValueMap& properties) : super(properties,
	FireElemental::MapKey,
	EntityResources::Enemies_DaemonsHallow_FireElemental_Animations,
	EntityResources::Enemies_DaemonsHallow_FireElemental_Emblem,
	Size(820.0f, 1480.0f),
	1.0f,
	Vec2(64.0f, 0.0f))
{
}

FireElemental::~FireElemental()
{
}

Vec2 FireElemental::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* FireElemental::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_FireElemental::create();
}
