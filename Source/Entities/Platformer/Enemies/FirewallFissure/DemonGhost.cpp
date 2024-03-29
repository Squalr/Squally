#include "DemonGhost.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonGhost::MapKey = "demon-ghost";

DemonGhost* DemonGhost::deserialize(ValueMap& properties)
{
	DemonGhost* instance = new DemonGhost(properties);

	instance->autorelease();

	return instance;
}

DemonGhost::DemonGhost(ValueMap& properties) : super(properties,
	DemonGhost::MapKey,
	EntityResources::Enemies_FirewallFissure_DemonGhost_Animations,
	EntityResources::Enemies_FirewallFissure_DemonGhost_Emblem,
	CSize(256.0f, 320.0f),
	0.7f,
	64.0f)
{
}

DemonGhost::~DemonGhost()
{
}

Vec2 DemonGhost::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* DemonGhost::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_FirewallFissure_DemonGhost::create();
}
