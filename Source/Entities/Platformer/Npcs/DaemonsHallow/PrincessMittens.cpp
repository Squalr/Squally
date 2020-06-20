#include "PrincessMittens.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PrincessMittens::MapKey = "princess-mittens";

PrincessMittens* PrincessMittens::deserialize(ValueMap& properties)
{
	PrincessMittens* instance = new PrincessMittens(properties);

	instance->autorelease();

	return instance;
}

PrincessMittens::PrincessMittens(ValueMap& properties) : super(properties,
	PrincessMittens::MapKey,
	EntityResources::Npcs_DaemonsHallow_PrincessMittens_Animations,
	EntityResources::Npcs_DaemonsHallow_PrincessMittens_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

PrincessMittens::~PrincessMittens()
{
}

Vec2 PrincessMittens::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* PrincessMittens::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_PrincessMittens::create();
}
