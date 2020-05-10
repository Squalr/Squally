#include "PrincessDawn.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PrincessDawn::MapKey = "princess-dawn";

PrincessDawn* PrincessDawn::deserialize(ValueMap& properties)
{
	PrincessDawn* instance = new PrincessDawn(properties);

	instance->autorelease();

	return instance;
}

PrincessDawn::PrincessDawn(ValueMap& properties) : super(properties,
	PrincessDawn::MapKey,
	EntityResources::Npcs_SeaSharpCaverns_PrincessDawn_Animations,
	EntityResources::Npcs_SeaSharpCaverns_PrincessDawn_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

PrincessDawn::~PrincessDawn()
{
}

Vec2 PrincessDawn::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* PrincessDawn::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_PrincessDawn::create();
}
