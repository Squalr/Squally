#include "Godiva.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Godiva::MapKey = "godiva";

Godiva* Godiva::deserialize(ValueMap& properties)
{
	Godiva* instance = new Godiva(properties);

	instance->autorelease();

	return instance;
}

Godiva::Godiva(ValueMap& properties) : super(properties,
	Godiva::MapKey,
	EntityResources::Npcs_VoidStar_Godiva_Animations,
	EntityResources::Npcs_VoidStar_Godiva_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Godiva::~Godiva()
{
}

Vec2 Godiva::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Godiva::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Godiva::create();
}
