#include "Mummy.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Mummy::MapKey = "mummy";

Mummy* Mummy::deserialize(ValueMap& properties)
{
	Mummy* instance = new Mummy(properties);

	instance->autorelease();

	return instance;
}

Mummy::Mummy(ValueMap& properties) : super(properties,
	Mummy::MapKey,
	EntityResources::Helpers_UnderflowRuins_Mummy_Animations,
	EntityResources::Helpers_UnderflowRuins_Mummy_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
}

Mummy::~Mummy()
{
}

Vec2 Mummy::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Mummy::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_UnderflowRuins_Mummy::create();
}
