#include "QueenElise.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string QueenElise::MapKey = "queen-elise";

QueenElise* QueenElise::deserialize(ValueMap& properties)
{
	QueenElise* instance = new QueenElise(properties);

	instance->autorelease();

	return instance;
}

QueenElise::QueenElise(ValueMap& properties) : super(properties,
	QueenElise::MapKey,
	EntityResources::Npcs_VoidStar_QueenElise_Animations,
	EntityResources::Npcs_VoidStar_QueenElise_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

QueenElise::~QueenElise()
{
}

Vec2 QueenElise::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* QueenElise::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_QueenElise::create();
}
