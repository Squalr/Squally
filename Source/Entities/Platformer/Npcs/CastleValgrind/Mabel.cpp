#include "Mabel.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Mabel::MapKey = "mabel";

Mabel* Mabel::deserialize(ValueMap& properties)
{
	Mabel* instance = new Mabel(properties);

	instance->autorelease();

	return instance;
}

Mabel::Mabel(ValueMap& properties) : super(properties,
	Mabel::MapKey,
	EntityResources::Npcs_CastleValgrind_Mabel_Animations,
	EntityResources::Npcs_CastleValgrind_Mabel_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Mabel::~Mabel()
{
}

Vec2 Mabel::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Mabel::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Mabel::create();
}
