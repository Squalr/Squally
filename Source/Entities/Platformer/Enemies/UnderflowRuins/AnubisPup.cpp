#include "AnubisPup.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AnubisPup::MapKey = "anubis-pup";

AnubisPup* AnubisPup::deserialize(ValueMap& properties)
{
	AnubisPup* instance = new AnubisPup(properties);

	instance->autorelease();

	return instance;
}

AnubisPup::AnubisPup(ValueMap& properties) : super(properties,
	AnubisPup::MapKey,
	EntityResources::Enemies_UnderflowRuins_AnubisPup_Animations,
	EntityResources::Enemies_UnderflowRuins_AnubisPup_Emblem,
	Size(128.0f, 186.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

AnubisPup::~AnubisPup()
{
}

Vec2 AnubisPup::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* AnubisPup::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_AnubisPup::create();
}
