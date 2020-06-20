#include "Ajax.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ajax::MapKey = "ajax";

Ajax* Ajax::deserialize(ValueMap& properties)
{
	Ajax* instance = new Ajax(properties);

	instance->autorelease();

	return instance;
}

Ajax::Ajax(ValueMap& properties) : super(properties,
	Ajax::MapKey,
	EntityResources::Npcs_UnderflowRuins_Ajax_Animations,
	EntityResources::Npcs_UnderflowRuins_Ajax_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Ajax::~Ajax()
{
}

Vec2 Ajax::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ajax::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Ajax::create();
}
