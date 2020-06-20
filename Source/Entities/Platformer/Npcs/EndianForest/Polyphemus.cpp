#include "Polyphemus.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Polyphemus::MapKey = "polyphemus";

Polyphemus* Polyphemus::deserialize(ValueMap& properties)
{
	Polyphemus* instance = new Polyphemus(properties);

	instance->autorelease();

	return instance;
}

Polyphemus::Polyphemus(ValueMap& properties) : super(properties,
	Polyphemus::MapKey,
	EntityResources::Npcs_EndianForest_Polyphemus_Animations,
	EntityResources::Npcs_EndianForest_Polyphemus_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Polyphemus::~Polyphemus()
{
}

Vec2 Polyphemus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Polyphemus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Polyphemus::create();
}
