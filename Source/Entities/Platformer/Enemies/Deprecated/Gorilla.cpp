#include "Gorilla.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Gorilla::MapKey = "gorilla";

Gorilla* Gorilla::deserialize(ValueMap& properties)
{
	Gorilla* instance = new Gorilla(properties);

	instance->autorelease();

	return instance;
}

Gorilla::Gorilla(ValueMap& properties) : super(properties,
	Gorilla::MapKey,
	EntityResources::Enemies__Deprecated_Gorilla_Animations,
	EntityResources::Enemies__Deprecated_Gorilla_Emblem,
	CSize(256.0f, 228.0f),
	1.0f)
{
}

Gorilla::~Gorilla()
{
}

Vec2 Gorilla::getDialogueOffset()
{
	return Vec2(-64.0f, -144.0f);
}

LocalizedString* Gorilla::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DataMines_Gorilla::create();
}
