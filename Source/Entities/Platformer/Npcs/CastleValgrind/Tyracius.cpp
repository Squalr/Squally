#include "Tyracius.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tyracius::MapKey = "tyracius";

Tyracius* Tyracius::deserialize(ValueMap& properties)
{
	Tyracius* instance = new Tyracius(properties);

	instance->autorelease();

	return instance;
}

Tyracius::Tyracius(ValueMap& properties) : super(properties,
	Tyracius::MapKey,
	EntityResources::Npcs_CastleValgrind_Tyracius_Animations,
	EntityResources::Npcs_CastleValgrind_Tyracius_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Tyracius::~Tyracius()
{
}

Vec2 Tyracius::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Tyracius::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Tyracius::create();
}
