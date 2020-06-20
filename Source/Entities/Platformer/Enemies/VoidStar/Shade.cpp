#include "Shade.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Shade::MapKey = "shade";

Shade* Shade::deserialize(ValueMap& properties)
{
	Shade* instance = new Shade(properties);

	instance->autorelease();

	return instance;
}

Shade::Shade(ValueMap& properties) : super(properties,
	Shade::MapKey,
	EntityResources::Enemies_VoidStar_Shade_Animations,
	EntityResources::Enemies_VoidStar_Shade_Emblem,
	Size(284.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Shade::~Shade()
{
}

Vec2 Shade::getDialogueOffset()
{
	return Vec2(0.0f, -312.0f);
}

LocalizedString* Shade::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_Shade::create();
}
