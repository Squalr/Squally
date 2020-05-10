#include "LionMan.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LionMan::MapKey = "lion-man";

LionMan* LionMan::deserialize(ValueMap& properties)
{
	LionMan* instance = new LionMan(properties);

	instance->autorelease();

	return instance;
}

LionMan::LionMan(ValueMap& properties) : super(properties,
	LionMan::MapKey,
	EntityResources::Enemies_UnderflowRuins_LionMan_Animations,
	EntityResources::Enemies_UnderflowRuins_LionMan_Emblem,
	Size(256.0f, 326.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

LionMan::~LionMan()
{
}

Vec2 LionMan::getDialogueOffset()
{
	return Vec2(-32.0f, -196.0f);
}

LocalizedString* LionMan::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_LionMan::create();
}
