#include "Ragnis.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ragnis::MapKey = "ragnis";

Ragnis* Ragnis::deserialize(ValueMap& properties)
{
	Ragnis* instance = new Ragnis(properties);

	instance->autorelease();

	return instance;
}

Ragnis::Ragnis(ValueMap& properties) : super(properties,
	Ragnis::MapKey,
	EntityResources::Npcs_DaemonsHallow_Ragnis_Animations,
	EntityResources::Npcs_DaemonsHallow_Ragnis_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

Ragnis::~Ragnis()
{
}

Vec2 Ragnis::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ragnis::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Ragnis::create();
}
