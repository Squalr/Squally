#include "Thor.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Thor::MapKey = "thor";

Thor* Thor::deserialize(ValueMap& properties)
{
	Thor* instance = new Thor(properties);

	instance->autorelease();

	return instance;
}

Thor::Thor(ValueMap& properties) : super(properties,
	Thor::MapKey,
	EntityResources::Npcs_UnderflowRuins_Thor_Animations,
	EntityResources::Npcs_UnderflowRuins_Thor_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Thor::~Thor()
{
}

Vec2 Thor::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Thor::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Thor::create();
}
