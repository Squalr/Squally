#include "SnowFiend.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SnowFiend::MapKey = "snow-fiend";

SnowFiend* SnowFiend::deserialize(ValueMap& properties)
{
	SnowFiend* instance = new SnowFiend(properties);

	instance->autorelease();

	return instance;
}

SnowFiend::SnowFiend(ValueMap& properties) : super(properties,
	SnowFiend::MapKey,
	EntityResources::Enemies_BalmerPeaks_SnowFiend_Animations,
	EntityResources::Enemies_BalmerPeaks_SnowFiend_Emblem,
	Size(420.0f, 420.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

SnowFiend::~SnowFiend()
{
}

Vec2 SnowFiend::getDialogueOffset()
{
	return Vec2(-32.0f, -248.0f);
}

LocalizedString* SnowFiend::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BalmerPeaks_SnowFiend::create();
}
