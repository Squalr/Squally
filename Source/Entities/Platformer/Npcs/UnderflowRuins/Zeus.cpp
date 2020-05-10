#include "Zeus.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Zeus::MapKey = "zeus";

Zeus* Zeus::deserialize(ValueMap& properties)
{
	Zeus* instance = new Zeus(properties);

	instance->autorelease();

	return instance;
}

Zeus::Zeus(ValueMap& properties) : super(properties,
	Zeus::MapKey,
	EntityResources::Npcs_UnderflowRuins_Zeus_Animations,
	EntityResources::Npcs_UnderflowRuins_Zeus_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Zeus::~Zeus()
{
}

Vec2 Zeus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Zeus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Zeus::create();
}
