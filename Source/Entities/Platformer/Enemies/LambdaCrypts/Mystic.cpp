#include "Mystic.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Mystic::MapKey = "mystic";

Mystic* Mystic::deserialize(ValueMap& properties)
{
	Mystic* instance = new Mystic(properties);

	instance->autorelease();

	return instance;
}

Mystic::Mystic(ValueMap& properties) : super(properties,
	Mystic::MapKey,
	EntityResources::Enemies_LambdaCrypts_Mystic_Animations,
	EntityResources::Enemies_LambdaCrypts_Mystic_Emblem,
	Size(420.0f, 296.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Mystic::~Mystic()
{
}

Vec2 Mystic::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Mystic::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_Mystic::create();
}
