#include "Scarecrow.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Scarecrow::MapKey = "scarecrow";

Scarecrow* Scarecrow::deserialize(ValueMap& properties)
{
	Scarecrow* instance = new Scarecrow(properties);

	instance->autorelease();

	return instance;
}

Scarecrow::Scarecrow(ValueMap& properties) : super(properties,
	Scarecrow::MapKey,
	EntityResources::Enemies_CastleValgrind_Scarecrow_Animations,
	EntityResources::Enemies_CastleValgrind_Scarecrow_Emblem,
	Size(196.0f, 512.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Scarecrow::~Scarecrow()
{
}

Vec2 Scarecrow::getDialogueOffset()
{
	return Vec2(0.0f, -312.0f);
}

LocalizedString* Scarecrow::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Scarecrow::create();
}
