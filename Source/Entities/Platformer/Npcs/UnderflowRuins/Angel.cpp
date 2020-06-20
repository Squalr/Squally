#include "Angel.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Angel::MapKey = "angel";

Angel* Angel::deserialize(ValueMap& properties)
{
	Angel* instance = new Angel(properties);

	instance->autorelease();

	return instance;
}

Angel::Angel(ValueMap& properties) : super(properties,
	Angel::MapKey,
	EntityResources::Npcs_UnderflowRuins_Angel_Animations,
	EntityResources::Npcs_UnderflowRuins_Angel_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Angel::~Angel()
{
}

Vec2 Angel::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Angel::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Angel::create();
}
