#include "Santa.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Santa::MapKey = "santa";

Santa* Santa::deserialize(ValueMap& properties)
{
	Santa* instance = new Santa(properties);

	instance->autorelease();

	return instance;
}

Santa::Santa(ValueMap& properties) : super(properties,
	Santa::MapKey,
	EntityResources::Enemies_BalmerPeaks_Santa_Animations,
	EntityResources::Enemies_BalmerPeaks_Santa_Emblem,
	Size(420.0f, 452.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Santa::~Santa()
{
}

Vec2 Santa::getDialogueOffset()
{
	return Vec2(-32.0f, -248.0f);
}

LocalizedString* Santa::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BalmerPeaks_Santa::create();
}
