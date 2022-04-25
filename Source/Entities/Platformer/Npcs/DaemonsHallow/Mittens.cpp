#include "Mittens.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Mittens::MapKey = "mittens";

Mittens* Mittens::deserialize(ValueMap& properties)
{
	Mittens* instance = new Mittens(properties);

	instance->autorelease();

	return instance;
}

Mittens::Mittens(ValueMap& properties) : super(properties,
	Mittens::MapKey,
	EntityResources::Npcs_DaemonsHallow_Mittens_Animations,
	EntityResources::Npcs_DaemonsHallow_Mittens_Emblem,
	CSize(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Mittens::~Mittens()
{
}

Vec2 Mittens::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Mittens::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Mittens::create();
}
