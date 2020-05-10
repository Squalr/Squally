#include "Drak.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Drak::MapKey = "drak";

Drak* Drak::deserialize(ValueMap& properties)
{
	Drak* instance = new Drak(properties);

	instance->autorelease();

	return instance;
}

Drak::Drak(ValueMap& properties) : super(properties,
	Drak::MapKey,
	EntityResources::Npcs_DaemonsHallow_Drak_Animations,
	EntityResources::Npcs_DaemonsHallow_Drak_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Drak::~Drak()
{
}

Vec2 Drak::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Drak::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Drak::create();
}
