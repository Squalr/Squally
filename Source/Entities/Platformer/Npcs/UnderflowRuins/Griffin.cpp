#include "Griffin.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Griffin::MapKey = "griffin";

Griffin* Griffin::deserialize(ValueMap& properties)
{
	Griffin* instance = new Griffin(properties);

	instance->autorelease();

	return instance;
}

Griffin::Griffin(ValueMap& properties) : super(properties,
	Griffin::MapKey,
	EntityResources::Npcs_UnderflowRuins_Griffin_Animations,
	EntityResources::Npcs_UnderflowRuins_Griffin_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Griffin::~Griffin()
{
}

Vec2 Griffin::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Griffin::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Griffin::create();
}
