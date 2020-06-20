#include "PrincessOpal.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PrincessOpal::MapKey = "princess-opal";

PrincessOpal* PrincessOpal::deserialize(ValueMap& properties)
{
	PrincessOpal* instance = new PrincessOpal(properties);

	instance->autorelease();

	return instance;
}

PrincessOpal::PrincessOpal(ValueMap& properties) : super(properties,
	PrincessOpal::MapKey,
	EntityResources::Npcs_CastleValgrind_PrincessOpal_Animations,
	EntityResources::Npcs_CastleValgrind_PrincessOpal_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

PrincessOpal::~PrincessOpal()
{
}

Vec2 PrincessOpal::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* PrincessOpal::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_PrincessOpal::create();
}
