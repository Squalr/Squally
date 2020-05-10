#include "Rhinoman.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Rhinoman::MapKey = "rhinoman";

Rhinoman* Rhinoman::deserialize(ValueMap& properties)
{
	Rhinoman* instance = new Rhinoman(properties);

	instance->autorelease();

	return instance;
}

Rhinoman::Rhinoman(ValueMap& properties) : super(properties,
	Rhinoman::MapKey,
	EntityResources::Enemies_SeaSharpCaverns_Rhinoman_Animations,
	EntityResources::Enemies_SeaSharpCaverns_Rhinoman_Emblem,
	Size(592.0f, 592.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Rhinoman::~Rhinoman()
{
}

Vec2 Rhinoman::getDialogueOffset()
{
	return Vec2(0.0f, -420.0f);
}

LocalizedString* Rhinoman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_Rhinoman::create();
}
