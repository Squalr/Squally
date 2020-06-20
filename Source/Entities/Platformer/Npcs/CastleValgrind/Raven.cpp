#include "Raven.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Raven::MapKey = "raven";

Raven* Raven::deserialize(ValueMap& properties)
{
	Raven* instance = new Raven(properties);

	instance->autorelease();

	return instance;
}

Raven::Raven(ValueMap& properties) : super(properties,
	Raven::MapKey,
	EntityResources::Npcs_CastleValgrind_Raven_Animations,
	EntityResources::Npcs_CastleValgrind_Raven_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Raven::~Raven()
{
}

Vec2 Raven::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Raven::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Raven::create();
}
