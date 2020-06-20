#include "Ralston.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ralston::MapKey = "ralston";

Ralston* Ralston::deserialize(ValueMap& properties)
{
	Ralston* instance = new Ralston(properties);

	instance->autorelease();

	return instance;
}

Ralston::Ralston(ValueMap& properties) : super(properties,
	Ralston::MapKey,
	EntityResources::Npcs_VoidStar_Ralston_Animations,
	EntityResources::Npcs_VoidStar_Ralston_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

Ralston::~Ralston()
{
}

Vec2 Ralston::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ralston::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Ralston::create();
}
