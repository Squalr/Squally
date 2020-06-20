#include "Appolo.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Appolo::MapKey = "appolo";

Appolo* Appolo::deserialize(ValueMap& properties)
{
	Appolo* instance = new Appolo(properties);

	instance->autorelease();

	return instance;
}

Appolo::Appolo(ValueMap& properties) : super(properties,
	Appolo::MapKey,
	EntityResources::Npcs_VoidStar_Appolo_Animations,
	EntityResources::Npcs_VoidStar_Appolo_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Appolo::~Appolo()
{
}

Vec2 Appolo::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Appolo::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Appolo::create();
}
