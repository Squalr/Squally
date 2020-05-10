#include "Vesuvius.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Vesuvius::MapKey = "vesuvius";

Vesuvius* Vesuvius::deserialize(ValueMap& properties)
{
	Vesuvius* instance = new Vesuvius(properties);

	instance->autorelease();

	return instance;
}

Vesuvius::Vesuvius(ValueMap& properties) : super(properties,
	Vesuvius::MapKey,
	EntityResources::Npcs_LambdaCrypts_Vesuvius_Animations,
	EntityResources::Npcs_LambdaCrypts_Vesuvius_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Vesuvius::~Vesuvius()
{
}

Vec2 Vesuvius::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Vesuvius::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Vesuvius::create();
}
