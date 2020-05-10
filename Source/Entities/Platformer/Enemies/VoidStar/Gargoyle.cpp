#include "Gargoyle.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Gargoyle::MapKey = "gargoyle";

Gargoyle* Gargoyle::deserialize(ValueMap& properties)
{
	Gargoyle* instance = new Gargoyle(properties);

	instance->autorelease();

	return instance;
}

Gargoyle::Gargoyle(ValueMap& properties) : super(properties,
	Gargoyle::MapKey,
	EntityResources::Enemies_VoidStar_Gargoyle_Animations,
	EntityResources::Enemies_VoidStar_Gargoyle_Emblem,
	Size(256.0f, 256.0f),
	0.9f,
	Vec2(-32.0f, 0.0f))
{
}

Gargoyle::~Gargoyle()
{
}

Vec2 Gargoyle::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Gargoyle::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_Gargoyle::create();
}
