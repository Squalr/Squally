#include "Barbarian.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Barbarian::MapKey = "barbarian";

Barbarian* Barbarian::deserialize(ValueMap& properties)
{
	Barbarian* instance = new Barbarian(properties);

	instance->autorelease();

	return instance;
}

Barbarian::Barbarian(ValueMap& properties) : super(properties,
	Barbarian::MapKey,
	EntityResources::Enemies_CastleValgrind_Barbarian_Animations,
	EntityResources::Enemies_CastleValgrind_Barbarian_Emblem,
	Size(256.0f, 228.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Barbarian::~Barbarian()
{
}

Vec2 Barbarian::getDialogueOffset()
{
	return Vec2(0.0f, -160.0f);
}

LocalizedString* Barbarian::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Barbarian::create();
}
