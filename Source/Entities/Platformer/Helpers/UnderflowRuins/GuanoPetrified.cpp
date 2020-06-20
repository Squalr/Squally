#include "GuanoPetrified.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GuanoPetrified::MapKey = "guano-petrified";

GuanoPetrified* GuanoPetrified::deserialize(ValueMap& properties)
{
	GuanoPetrified* instance = new GuanoPetrified(properties);

	instance->autorelease();

	return instance;
}

GuanoPetrified::GuanoPetrified(ValueMap& properties) : super(properties,
	GuanoPetrified::MapKey,
	EntityResources::Helpers_UnderflowRuins_GuanoPetrified_Animations,
	EntityResources::Helpers_UnderflowRuins_GuanoPetrified_Emblem,
	Size(64.0f, 128.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

GuanoPetrified::~GuanoPetrified()
{
}

Vec2 GuanoPetrified::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* GuanoPetrified::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_EndianForest_Guano::create();
}
