#include "Yeti.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Yeti::MapKey = "yeti";

Yeti* Yeti::deserialize(ValueMap& properties)
{
	Yeti* instance = new Yeti(properties);

	instance->autorelease();

	return instance;
}

Yeti::Yeti(ValueMap& properties) : super(properties,
	Yeti::MapKey,
	EntityResources::Enemies_BalmerPeaks_Yeti_Animations,
	EntityResources::Enemies_BalmerPeaks_Yeti_Emblem,
	Size(380.0f, 572.0f),
	1.0f,
	Vec2(24.0f, 0.0f))
{
}

Yeti::~Yeti()
{
}

Vec2 Yeti::getDialogueOffset()
{
	return Vec2(-64.0f, -160.0f);
}

LocalizedString* Yeti::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BalmerPeaks_Yeti::create();
}
